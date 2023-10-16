package contact;
//Brandon Goller

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class ContactService {
    private Map<String, Contact> contacts;

    public ContactService() {
        this.contacts = new HashMap<>();
    }

    public boolean addContact(Contact contact) {
        if (!contacts.containsKey(contact.getContactId())) {
            contacts.put((String) contact.getContactId(), contact);
            return true;
        }
        return false;
    }

    public boolean deleteContact(String contactId) {
        if (contacts.containsKey(contactId)) {
            contacts.remove(contactId);
            return true;
        }
        return false;
    }

    public boolean updateContact(Contact updatedContact) {
        String contactId = (String) updatedContact.getContactId();
        if (contacts.containsKey(contactId)) {
            contacts.put(contactId, updatedContact);
            return true;
        }
        return false;
    }

    public Contact getContact(String contactId) {
        return contacts.get(contactId);
    }

    public List<Contact> getAllContacts() {
        return new ArrayList<>(contacts.values());
    }
}
