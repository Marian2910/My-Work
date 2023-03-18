package socialnetwork.domain;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class User extends Entity<String> {
    private String firstName;
    private String lastName;
    private String password;

    public User(String id, String firstName, String lastName, String password) {
        super(id);
        this.firstName = firstName;
        this.lastName = lastName;
        this.password = password;
    }


    public String getFirstName() {
        return firstName;
    }

    public void setFirstName(String firstName) {
        this.firstName = firstName;
    }

    public String getLastName() {
        return lastName;
    }

    public void setLastName(String lastName) {
        this.lastName = lastName;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

//    public void addFriend(User user){
//        this.friends.add(user);
//    }
//    public void deleteFriend(User user){
//        this.friends.remove(user);
//    }
//
//    public List<User> getFriends() {
//        return friends;
//    }

    @Override
    public String toString() {
        StringBuilder friendsString = new StringBuilder();
        return "User{" + "user_name=" + this.getId() + '\'' +
                ", firstName='" + this.firstName + '\'' +
                ", lastName='" + this.lastName +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof User that)) return false;
        return getFirstName().equals(that.getFirstName()) &&
                getLastName().equals(that.getLastName());
    }

    @Override
    public int hashCode() {
        return Objects.hash(getFirstName(), getLastName());
    }
}