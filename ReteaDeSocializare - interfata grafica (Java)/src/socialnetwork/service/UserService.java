//package socialnetwork.service;
//
//import socialnetwork.domain.User;
//import socialnetwork.domain.validators.ValidationException;
//import socialnetwork.repository.Repository;
//
//
//import java.util.ArrayList;
//import java.util.List;
//
//import java.util.Objects;
//import java.util.Optional;
//
//public class UserService {
//    private final Repository<Long, User> repo;
//
//    public UserService(Repository<Long, User> repo) {
//        this.repo = repo;
//    }
//
//    public void addUser(Long id, String firstName, String lastName, String password) {
//        User user = new User(id, firstName, lastName, password);
//        if(repo.findOne(id).isPresent())
//            throw new ValidationException("There is already an user with this id, try again");
//        else repo.save(user);
//    }
//
//    public void updateUser(Long id, String firstName, String lastName, String password) {
//        User user = new User(id, firstName, lastName, password, repo.findOne(id).get().getFriends());
//        repo.update(user);
//    }
//
//    public void deleteUser(long id) {
//            repo.delete(id);
//
//    }
//    public Optional<User> getOneUser(long id) {
//        return repo.findOne(id);
//    }
//    public List<User> getAllUsers(){
//        return (List<User>) repo.findAll();
//    }
//    public void makeFriends(Long id, Long idFriend) {
//        User user1 = this.repo.findOne(id).get();
//        User user2 = this.repo.findOne(idFriend).get();
//
//        if (Objects.equals(user1, user2))
//            throw new ValidationException("\nYou cannot be friend with yourself :( !\n");
//
//        if (checkFriends(user1, user2))
//            throw new ValidationException("\nYou are already friends!\n");
////       repo.makeFriends(this.repo.findOne(id).get(), this.repo.findOne(idFriend).get());
//        user1.addFriend(user2);
//        user2.addFriend(user1);
//    }
//
//    private boolean checkFriends(User u1, User u2) {
//        List<User> friends = u1.getFriends();
//
//        for (User friend : friends) {
//            if (friend == u2)
//                return true;
//        }
//        return false;
//    }
//
//    public void deleteFriend(Long id, Long idFriend) {
//        User user1 = this.repo.findOne(id).get();
//        User user2 = this.repo.findOne(idFriend).get();
//
//        if (Objects.equals(user1, user2))
//            throw new ValidationException("\n You entered your id, not valid!!\n");
//
//        if (!checkFriends(user1, user2))
//            throw new ValidationException("\nThe user is not your friend!\n");
//        user1.deleteFriend(user2);
//        user2.deleteFriend(user1);
//    }
//
//    public List<User> friends(Long id) {
//        User user = this.repo.findOne(id).get();
//        List<User> friends = user.getFriends();
//        if (friends.size() == 0)
//            try {
//                throw new ValidationException("\nYou have no friends!\n");
//            } catch (ValidationException v) {
//                System.out.println(v.getMessage());
//            }
//        return friends;
//    }
//
//    public List<String> displayFriends(Long id) {
//            User user = this.repo.findOne(id).get();
//            List<User> friends = user.getFriends();
//            List<String> toDisplayFriends = new ArrayList<>();
//
//            try{
//            if (friends.size() == 0) {
//                throw new ValidationException("\nYou have no friends!\n");
//            } else {
//                for (User friend : friends) {
//                    toDisplayFriends.add("[ "+friend.getId()+". "+friend.getFirstName()+" "+friend.getLastName()+" ]");
//                }
//            }}
//            catch (ValidationException v){
//                System.out.println(v.getMessage());
//        }
//        return toDisplayFriends;
//    }
//
//
//
//    public void deleteAllFriends(long id) {
//        User user1 = this.repo.findOne(id).get();
//        List<User> friends = friends(id);
//        for (User u : friends) {
//            u.deleteFriend(user1);
//        }
//    }
//}
