package contact;
//Brandon Goller

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

public class ContactTest {
    private Contact contact;

    @BeforeEach
    public void setUp() {
        contact = new Contact("12345", "John", "Doe", "1234567890", "123 Main St");
    }

    @Test
    public void testValidContactCreation() {
        assertNotNull(contact);
        assertEquals("12345", contact.getContactId());
        assertEquals("John", contact.getFirstName());
        assertEquals("Doe", contact.getLastName());
        assertEquals("1234567890", contact.getPhone());
        assertEquals("123 Main St", contact.getAddress());
    }

    @Test
    public void testInvalidContactCreation() {
        // Test creating a contact with invalid inputs
        assertThrows(IllegalArgumentException.class, () -> new Contact("12345678901", "John", "Doe", "1234567890", "123 Main St"));
        assertThrows(IllegalArgumentException.class, () -> new Contact("12345", null, "Doe", "1234567890", "123 Main St"));
        assertThrows(IllegalArgumentException.class, () -> new Contact("12345", "John", "Doe", "1234", "123 Main St"));
        assertThrows(IllegalArgumentException.class, () -> new Contact("12345", "John", "Doe", "1234567890", null));
    }

    @Test
    public void testUpdateContact() {
        contact.setFirstName("Jane");
        contact.setLastName("Smith");
        contact.setPhone("9876543210");
        contact.setAddress("456 Elm St");

        assertEquals("Jane", contact.getFirstName());
        assertEquals("Smith", contact.getLastName());
        assertEquals("9876543210", contact.getPhone());
        assertEquals("456 Elm St", contact.getAddress());
    }

    @Test
    public void testEqualsMethod() {
        Contact contact1 = new Contact("12345", "John", "Doe", "1234567890", "123 Main St");
        Contact contact2 = new Contact("12345", "Jane", "Smith", "9876543210", "456 Elm St");
        Contact contact3 = new Contact("67890", "Alice", "Johnson", "5555555555", "789 Oak St");

        assertTrue(contact1.equals(contact2)); // Two contacts with the same contactId should be equal
        assertFalse(contact1.equals(contact3)); // Two contacts with different contactIds should not be equal
    }
}

