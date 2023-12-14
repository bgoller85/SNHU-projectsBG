from pymongo import MongoClient
from bson.objectid import ObjectId

class AnimalShelter(object):
    """ CRUD operations for Animal collection in MongoDB """

    def __init__(self):
        # Initialize Connection
        USER = 'aacuser'
        PASS = 'Brandon1' 
        HOST = 'nv-desktop-services.apporto.com'
        PORT = 30885
        DB = 'AAC'
        COL = 'animals'

        self.client = MongoClient('mongodb://%s:%s@%s:%d' % (USER, PASS, HOST, PORT))
        self.database = self.client[DB]
        self.collection = self.database[COL]

    def create(self, data):
        if data is not None:            
            result = self.database.animals.insert_one(data) # data should be dictionary     
            return result.acknowledged
        else:
            raise Exception("Nothing to save, because data parameter is empty")

    def read(self, query):
        """Query for documents from the specified MongoDB database and collection."""
        cursor = self.collection.find(query)
        result = list(cursor)
        return result
    
    def update(self, query, update_data):
        """Update document(s) in the specified MongoDB database and collection."""
        result = self.collection.update_many(query, {'$set': update_data})
        return result.modified_count

    def delete(self, query):
        """Delete document(s) from the specified MongoDB database and collection."""
        result = self.collection.delete_many(query)
        return result.deleted_count
