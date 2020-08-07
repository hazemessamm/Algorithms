from kdc import KDC
import random
from Crypto.Cipher import DES

kdc = KDC()

class Entities:
    def __init__(self, id=None, encoding='utf-8'):
        if id is None:
            raise Exception('id should have value')
        else:
            self.id = id
            
        self.encoding_type = encoding
        self.master_key = None
        self.encryption_tool = None
        self.session_key = None
        self.current_initiator = None
        
        self.session_info = []
        self.recieved_info = []
        self.states = {}
        
    #connects to the kdc by getting a master key and allocate it at the KDC for later uses
    def connect_to_kdc(self):
        self.master_key = kdc.allocate_master_key(self.id)
        self.encryption_tool = DES.new(self.master_key, mode=DES.MODE_ECB)
    
    #used to start communication with another entity
    #show_info variable is used if you want to print the details of what is happening
    def communicate_with(self, entity=None, show_info=False):
        current_nonce = self.generate_nonce()
        self.session_info.append(kdc.allocate_session_key(self.id, entity, current_nonce))
        self.session_key = self.encryption_tool.decrypt(self.get_initiator_info()[0])
        if show_info:
            print(f'Initiator {self.id} sent to KDC {self.id, entity, current_nonce}')
            print(f'Encrypted Session Key for Entity {self.id} : {self.get_initiator_info()}')
            print(f'Encrypted Session Key for Entity {entity} : {self.get_responder_info()}')
    
    #helper function to get the responder info the send them to the responder
    def get_responder_info(self):
        return self.session_info[-1][-1]
    
    #helper function to get the initiator info
    def get_initiator_info(self):
        return self.session_info[0][0]
    
    #used to authenticate between the two entities
    def authenticate(self, decrypted_key=None):
        return decrypted_key == self.session_key
    
    #used for encryptions using the master key
    def encrypt(self, value=None):
        if isinstance(value, str):
            return self.encryption_tool.encrypt(bytes(value, encoding=self.encoding_type), DES.MODE_ECB)
        else:
            return self.encryption_tool.encrypt(value, DES.MODE_ECB)
    
    #used for decryptions using the master key
    def decrypt(self, value=None):
        if isinstance(value, str):
            return self.encryption_tool.decrypt(bytes(value, encoding=self.encoding_type), DES.MODE_ECB)
        else:
            return self.encryption_tool.decrypt(value, DES.MODE_ECB)
    
    #send the responder info to the responder
    def send_info(self, responder=None, info=None, show_info=False):
        responder.recieved_info = info
        responder.preprocess_info()
    
    #preprocessing info like getting the session key from the info or getting the current initiator
    #Usually used by the responder 
    def preprocess_info(self, show_info=True):
        self.session_key = self.encryption_tool.decrypt(self.recieved_info[0])
        self.current_initiator = str(self.encryption_tool.decrypt(self.recieved_info[1]), encoding=self.encoding_type)
        if show_info:
            print(f'Session Key: {self.session_key}')
            print(f'Current Initiator: {self.current_initiator}')
            
    
    def generate_nonce(self):
        return random.getrandbits(10)
    
    #for DES purposes
    def pad(self, word=None):
        while len(word) != 8:
            word += ' '
        return word
    
    #method used to authenticate the initiator
    #used by the responder to authenticate the entity of the initiator
    def authenticate_initiator(self, show_info=True):
        current_nonce = bytes(self.pad(str(self.generate_nonce())), encoding=self.encoding_type)
        if show_info:
            print("Before Encrpytion: ", current_nonce)
        return DES.new(self.session_key, DES.MODE_ECB).encrypt(current_nonce)
    
    #used by the initiator to ensure to the responder
    def decrypt_authentication(self, value=None):
        return DES.new(self.session_key, DES.MODE_ECB).decrypt(value)
    
    #applied function to ensure the entity of the responder by applying random stuff on nonce value
    #authentication step
    def apply_function(self, value=None):
        applied = str()
        for i in value:
            applied += chr(i+1)
        applied = bytes(applied, encoding=self.encoding_type)
        return applied, DES.new(self.session_key, DES.MODE_ECB).encrypt(applied)
    
    #reversed function used by the responder to send back the nonce value without modifications
    #authentication step
    def reverse_function(self, value=None):
        value = DES.new(self.session_key, DES.MODE_ECB).decrypt(value)
        applied = str()
        for i in value:
            applied += chr(i-1)
        applied = bytes(applied, encoding=self.encoding_type)
        return applied
    
    
    

    
#three entities
a = Entities('a')
b = Entities('b')
c = Entities('c')

#connects to the KDC to get master keys
a.connect_to_kdc()
b.connect_to_kdc()
c.connect_to_kdc()


#entity A wants to communicate with entity B
a.communicate_with('b', show_info=True)

#entity A sends the information of the session key and other stuff to entity B to decrypt them
a.send_info(b, a.get_responder_info(), show_info=True)

#entity B wants to authenticate that entity A is the sender so it uses authenticate_initiator method
encrypted_nonce = b.authenticate_initiator()

print("Encrypted Nonce: ", encrypted_nonce)
#entity A decrypts the encrypted nonce generated by entity B
decrypted_nonce = a.decrypt_authentication(encrypted_nonce)
print(decrypted_nonce)

#entity A sends the decrypted nonce but with some changes to ensure that entity B is real
mutated_nonce, encrypted_mutation = a.apply_function(decrypted_nonce)

print(mutated_nonce)

#B reverse the changes that entity A made
print(b.reverse_function(encrypted_mutation))
