package contact;
//Brandon Goller

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

public class ContactServiceTest {
    private ContactService contactService;

    @BeforeEach
    public void setUp() {
        contactService = new ContactService();
    }

    @Test
    public void testAddContact() {
        Contact contact = new Contact("12345", "John", "Doe", "1234567890", "123 Main St");
        assertTrue(contactService.addContact(contact));
        assertEquals(contact, contactService.getContact("12345"));
    }

    @Test
    public void testDeleteContact() {
        Contact contact = new Contact("12345", "John", "Doe", "1234567890", "123 Main St");
        contactService.addContact(contact);
        assertTrue(contactService.deleteContact("12345"));
        assertNull(contactService.getContact("12345"));
    }

    @Test
    public void testUpdateContact() {
        Contact contact = new Contact("12345", "John", "Doe", "1234567890", "123 Main St");
        contactService.addContact(contact);

        Contact updatedContact = new Contact("12345", "Jane", "Smith", "9876543210", "456 Elm St");
        assertTrue(contactService.updateContact(updatedContact));

        Contact retrievedContact = contactService.getContact("12345");
        assertEquals("Jane", retrievedContact.getFirstName());
        assertEquals("Smith", retrievedContact.getLastName());
        assertEquals("9876543210", retrievedContact.getPhone());
        assertEquals("456 Elm St", retrievedContact.getAddress());
    }

    @Test
    public void testAddDuplicateContact() {
        Contact contact1 = new Contact("12345", "John", "Doe", "1234567890", "123 Main St");
        Contact contact2 = new Contact("12345", "Jane", "Smith", "9876543210", "456 Elm St");

        assertTrue(contactService.addContact(contact1));
        assertFalse(contactService.addContact(contact2)); // Adding a duplicate contact should fail
    }

    @Test
    public void testDeleteNonExistentContact() {
        assertFalse(contactService.deleteContact("99999")); // Trying to delete a non-existent contact should fail
    }

    @Test
    public void testUpdateNonExistentContact() {
        Contact contact = new Contact("12345", "John", "Doe", "1234567890", "123 Main St");
        assertFalse(contactService.updateContact(contact)); // Updating a non-existent contact should fail
    }

    @Test
    public void testGetAllContacts() {
        Contact contact1 = new Contact("12345", "John", "Doe", "1234567890", "123 Main St");
        Contact contact2 = new Contact("67890", "Jane", "Smith", "9876543210", "456 Elm St");

        contactService.addContact(contact1);
        contactService.addContact(contact2);

        assertEquals(2, contactService.getAllContacts().size());
    }
}

