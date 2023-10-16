package contact;
//Author Brandon Goller

import java.util.Objects;

public class Contact {
    private String contactId;
    private String firstName;
    private String lastName;
    private String phone;
    private String address;

    public Contact(String contactId, String firstName, String lastName, String phone, String address) {
        setContactId(contactId);
        setFirstName(firstName);
        setLastName(lastName);
        setPhone(phone);
        setAddress(address);
    }

    // Getters for all fields (contactId, firstName, lastName, phone, address)
    public String getContactId() {
        return contactId;
    }

    public String getFirstName() {
        return firstName;
    }

    public String getLastName() {
        return lastName;
    }

    public String getPhone() {
        return phone;
    }

    public String getAddress() {
        return address;
    }

    // Setter methods for all fields
    private void setContactId(String contactId) {
        // Check for null and length <= 10
        if (contactId != null && contactId.length() <= 10) {
            this.contactId = contactId;
        } else {
            throw new IllegalArgumentException("Contact ID must not be null and should have a length of at most 10 characters.");
        }
    }

    void setFirstName(String firstName) {
        // Check for null and length <= 10
        if (firstName != null && firstName.length() <= 10) {
            this.firstName = firstName;
        } else {
            throw new IllegalArgumentException("First Name must not be null and should have a length of at most 10 characters.");
        }
    }

    void setLastName(String lastName) {
        // Check for null and length <= 10
        if (lastName != null && lastName.length() <= 10) {
            this.lastName = lastName;
        } else {
            throw new IllegalArgumentException("Last Name must not be null and should have a length of at most 10 characters.");
        }
    }

    void setPhone(String phone) {
        // Check for null and ensure exactly 10 digits
        if (phone != null && phone.matches("\\d{10}")) {
            this.phone = phone;
        } else {
            throw new IllegalArgumentException("Phone number must not be null and should have exactly 10 digits.");
        }
    }

    void setAddress(String address) {
        // Check for null and length <= 30
        if (address != null && address.length() <= 30) {
            this.address = address;
        } else {
            throw new IllegalArgumentException("Address must not be null and should have a length of at most 30 characters.");
        }
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }
        if (obj == null || getClass() != obj.getClass()) {
            return false;
        }
        Contact contact = (Contact) obj;
        return contactId.equals(contact.contactId);
    }

    @Override
    public int hashCode() {
        return Objects.hash(contactId);
    }
}
