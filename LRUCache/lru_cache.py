class LRUCache:
    '''
    LRU cache stands for (L)east (R)ecently (U)sed cache.
    This algorithm removes the least used element from the cache
    and also it's used to get any element in very fast time
    that's why we use set() which has speed of O(1) in lookup or insert or delete
    we also use dictionary for tracking the value of each key
    we use the set() to lookup if the key exists or not
    then when we get any element that means that we used it so we pop it and put it back in the front
    because adding it in the front means that it's the most recent element we used so we don't want it to 
    be at the last or in the middle we need it in the front.

    Check out GeeksforGeeks C++ implementation https://www.geeksforgeeks.org/lru-cache-implementation/
    Check out interview cake for more explaination https://www.interviewcake.com/concept/java/lru-cache
    '''
    def __init__(self, capacity=None):
        if capacity == None:
            self.capacity = 120
        else:
            self.capacity = capacity
        self.cache = set()
        self.tracker = dict()

    def get(self, key) -> int:
        #check whether the key that the user wants exists or not
        if key in self.cache:
            '''
            if it exists then we pop the key from the tracker and store the value of that key
            then we add this key value pairs at the front of the tracker
            we added it in the front because when the user used the get() method that
            means that this key is important and used, then we need it to be at the front 
            because of it's importance
            '''
            value = self.tracker.pop(key)
            '''
            this method adds the key value pairs in the front without updating
            the cache because we don't need to update it because the key is already in the cache
            '''
            self.prepend_without_cache_update({key: value})
            return value
        else:
            #if it doesn't exist then we return -1
            return -1

    def prepend_without_cache_update(self, dictionary: dict) -> None:
        '''
        this function takes a dictionary which contains the key value pair
        that we need to add it in the front
        we use the update method to add key value pair in the front
        dictionary.update(self.tracker) -> this part adds the self.tracker information
        to the dictionary that means that the contents of the dictionary will be in the front
        and the contents of the self.tracker will be after it
        then we update the tracker by making it equal to the dictionary
        '''
        dictionary.update(self.tracker)
        self.tracker = dictionary


    def prepend_with_cache_update(self, dictionary: dict, key) -> None:
        '''
        if the user entered a new element then we need to add it in the front
        and add the key in the cache
        '''
        self.prepend_without_cache_update(dictionary=dictionary)
        self.cache.add(key)

    def pop_least_used_from_cache_and_tracker(self) -> None:
        '''
        here we pop the very last element from the tracker 
        the last element is the least used one that's why this element
        is the last element in the tracker.
        we also should remove it from the cache
        '''
        rm_key, _ = self.tracker.popitem()
        self.cache.remove(rm_key)
    
    def pop_from_tracker_and_update(self, dictionary: dict, key: int) -> None:
        '''
        this method is used when the user wants to add a new element that has the same key
        we remove the key from the tracker then we re-add it with the new element that the user entered
        example:
        if the tracker has {1: 2, 3: 4}
        and the users wants to add new element which has key = 1 and element = 5
        then we pop the {1: 2} by using pop(1) from the tracker and re-add it so the tracker will be
        {1: 5, 3: 4}        
        '''
        _ = self.tracker.pop(key)
        self.prepend_without_cache_update(dictionary)

    def add(self, key: int, value: int) -> None:

        #if the key is already in the tracker
        if key in self.tracker:
            self.pop_from_tracker_and_update({key: value}, key)

        #if we reach maximum capacity we need to remove the least used element (last one) from the dictionary
        #then add the new element
        elif len(self.cache) == self.capacity:
            self.pop_least_used_from_cache_and_tracker()
            self.prepend_with_cache_update({key: value}, key)
        else:
            self.prepend_with_cache_update({key: value}, key)
    
    def display(self) -> None:
        '''
        this function prints the elements from the most used to the least used
        '''
        for key, value in self.tracker.items():
            print("Key: ", key, "Value: ", value)


lru = LRUCache(3)
lru.add(1, 2)
lru.add(2, 32)
lru.add(4, 25)
lru.add(13, 26)
lru.add(4, 5)
lru.display()
