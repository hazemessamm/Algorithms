import random
import string
from Crypto.Cipher import DES


class KDC:
    def __init__(self, session_len=8, encoding='utf-8'):
        #to store master keys for every entity
        #the key is the entity id and the value is the key
        self.master_keys = {}
        self.session_len = session_len
        #encoding type that will be used when converting to bytes
        self.encoding_type = encoding
    
    #Used to generate a master key when an entity connects to the KDC
    def generate_master_key(self):
        current_key = ''.join(random.choice(string.ascii_uppercase + string.digits) for _ in range(8))
        while current_key in self.master_keys.values():
            current_key = ''.join(random.choice(string.ascii_uppercase + string.digits) for _ in range(8)) 
        return bytes(current_key, encoding=self.encoding_type)
    
    #generates session key and return it as bytes because I am using DES
    def generate_session_key(self):
        return bytes(''.join(random.choice(string.ascii_uppercase + string.digits) for _ in range(self.session_len)), encoding=self.encoding_type)
    
    #Used to generate the master key for the connected entity and save it for later uses
    def allocate_master_key(self, entity_id=None):
        current_master_key = self.generate_master_key()
        entity_id = self.pad(str(entity_id))
        self.master_keys[entity_id] = current_master_key
        return current_master_key
    
    #padding for the DES in case of the key is less than 8 bytes
    def pad(self, word=None):
        while len(word) != self.session_len:
            word += ' '
        return word
    
    #Used when the entity wants to communicate with another entity, KDC generates the session key
    #by taking the initiator id and responder id to register everything and also taking the nonce
    def allocate_session_key(self, initiator_id=None, responder_id=None, nonce=None):
        
        #the modified variables are created to work on them because I want to return the results to the user without any changes
        #or modifications to be clear output
        initiator_id_modified = self.pad(str(initiator_id)) 
        responder_id_modified = self.pad(str(responder_id))
        
        #getting the initiator and responder master key from a dictionary to encrypt the output using both of them
        initiator_key = self.master_keys.get(initiator_id_modified)
        responder_key = self.master_keys.get(responder_id_modified)
        
        #generates the session key
        session_key = self.generate_session_key()
        
        #creates a DES objects for initiator and responder to encrypt the result to ensure that only the initiator and responder
        #will decrypt them
        encrypted_initiator_msg = DES.new(initiator_key, mode=DES.MODE_ECB)
        encrypted_responder_msg = DES.new(responder_key, mode=DES.MODE_ECB)
        
        #it returns a list with two indexes the first one contains the output of the initiator which is the session key encrypted
        #by the initiator master key and the initiator id, responder id and the nonce
        #the second label contains the responder Id which will be sent by the initiator to the responder
        return [[encrypted_initiator_msg.encrypt(session_key), (initiator_id, responder_id, nonce)], 
                [encrypted_responder_msg.encrypt(session_key), encrypted_responder_msg.encrypt(bytes(initiator_id_modified, encoding=self.encoding_type))]]
                
        
        
        
