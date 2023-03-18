package socialnetwork.service;

import socialnetwork.domain.Friendship;
import socialnetwork.domain.User;
import socialnetwork.domain.validators.ValidationException;
import socialnetwork.repository.Repository;
import socialnetwork.utils.events.ChangeEventType;
import socialnetwork.utils.events.FriendshipEntityChangeEvent;
import socialnetwork.utils.observer.Observable;
import socialnetwork.utils.observer.Observer;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

public class Service implements Observable<FriendshipEntityChangeEvent> {
    private Repository<String, User> userRepository;
    private Repository<String, Friendship> friendshipRepository;

    private String currentUserId = null;

    private List<Observer<FriendshipEntityChangeEvent>> observers= new ArrayList<>();

    public Service(Repository<String, User> UserRepository, Repository<String, Friendship> FriendshipRepository) {
        this.userRepository = UserRepository;
        this.friendshipRepository = FriendshipRepository;
    }

    public void printUsers(){
        for(User u: userRepository.findAll()){
            System.out.println(u);
        }
    }
    public void printFriendships(){
        for(Friendship f: friendshipRepository.findAll()){
            System.out.println(f);
        }
    }

    public boolean userLogIn(String id, String password) {
        for (User user : userRepository.findAll()) {
            if (user.getId().equals(id)) {
                if (user.getPassword().equals(password)) {
                    currentUserId = user.getId();
                    return true;
                } else {
                    return false;
                }
            }
        }
        return false;
    }

    public boolean userSignUp(String id, String firstName, String lastName, String password) {
        for (User user : userRepository.findAll()) {
            if (user.getId().equals(id)){
                return false;
            }
        }
        try {
            User u = new User(null, firstName,lastName,password);
            userRepository.save(u);
            currentUserId = u.getId();
        } catch (Error e) {
            System.out.println(e.getMessage());
        }
        return true;
    }

    public void userLogOut() {
        currentUserId = null;
    }

    /**
     * Add a friend to the current user
     *
     * @param Id String
     */
    public void addFriend(String Id, LocalDateTime data) {
        User userA = userRepository.findOne(currentUserId);
        User userB = userRepository.findOne(Id);
        if (userB == null || userA == null) {
            throw new Error("The user doesn't exist!");
        }
        List<Friendship> lst = getFriendships();
        for(Friendship el: lst){
            if((el.getIdFriend1().equals(userA.getId()) && el.getIdFriend2().equals(userB.getId())) || (el.getIdFriend1().equals(userB.getId()) && el.getIdFriend2().equals(userA.getId()))){
                throw new ValidationException("Prietenia deja exista!");
            }
        }
        friendshipRepository.save(new Friendship(null, currentUserId, Id,data));
    }
    public void sendRequest(String Id){
        User userA = userRepository.findOne(currentUserId);
        User userB = userRepository.findOne(Id);

        List<Friendship> lst = getFriendships();
        for(Friendship el:lst){
            if(el.getIdFriend1().equals(userA.getId()) && el.getIdFriend2().equals(userB.getId())){
                throw new ValidationException("You have already sent a friend request!");
            }
        }

        Friendship el=new Friendship(null, currentUserId, Id);
        friendshipRepository.save(el);
        notifyObservers(new FriendshipEntityChangeEvent(ChangeEventType.ADD, el));
    }

    public void acceptRequest(String Id){
        User user = userRepository.findOne(Id);
        List<Friendship> list = getFriendships();
        //for(Prietenie el:lst) System.out.println(el);
        for(Friendship el: list){
            if(el.getIdFriend1().equals(user.getId()) && el.getPending()) {
                //System.out.println("BA L-A GASIT");
                Friendship newFriendship = new Friendship(el.getId(),el.getIdFriend1(),el.getIdFriend2(),el.getData(),false);
                //el.setPending(false);
                friendshipRepository.update(el, newFriendship);
                notifyObservers(new FriendshipEntityChangeEvent(ChangeEventType.ADD, newFriendship));
                break;
            }
        }
    }

    public Friendship deleteFriend(String friend1, String friend2) {
        List<Friendship> list = friendshipRepository.findAll();

        for(Friendship el:list){
            if((el.getIdFriend1().equals(friend1) && el.getIdFriend2().equals(friend2)) || (el.getIdFriend1().equals(friend2) && el.getIdFriend2().equals(friend1))){

                    friendshipRepository.delete(el);
                notifyObservers(new FriendshipEntityChangeEvent(ChangeEventType.ADD, el));
                return el;
            }
        }
        throw new ValidationException("You are not friends!");
    }

    public List<Friendship> getFriendships() {
        List<Friendship> prietenii = new ArrayList<>();
        for (Friendship fr : friendshipRepository.findAll()) {
            if (fr.getIdFriend1().equals(currentUserId) || fr.getIdFriend2().equals(currentUserId)) {
                prietenii.add(fr);
            }
        }
        return prietenii;
    }

    public List<User> getUserRequests() {
        List<User> friendships = new ArrayList<>();
        for (Friendship fr : friendshipRepository.findAll()) {
            if (fr.getIdFriend2().equals(currentUserId) && fr.getPending()) {
                friendships.add(userRepository.findOne(fr.getIdFriend1()));
            }
        }
        return friendships;
    }

    public List<User> getUsersFriends() {
        List<User> friendships = new ArrayList<>();
        for (Friendship fr : friendshipRepository.findAll()) {
            if ((fr.getIdFriend1().equals(currentUserId) || fr.getIdFriend2().equals(currentUserId)) && !fr.getPending()) {
                if(!fr.getIdFriend1().equals(currentUserId))  friendships.add(userRepository.findOne(fr.getIdFriend1()));
                else friendships.add(userRepository.findOne(fr.getIdFriend2()));
            }
        }
        return friendships;
    }

    public List<User> getUsersNotFriends() {
        Boolean ok=true;
        List<User> notFriends = new ArrayList<>();
        List<User> list = getUsersFriends();
        list.addAll(getUserRequests());
        for(User user: userRepository.findAll()){
            for (User u : list) {
                if (user.getId().equals(u.getId())) ok = false;
            }
            if(ok == true && !user.getId().equals(currentUserId)) notFriends.add(user);
            ok=true;
        }
        return notFriends;
    }

    public void eraseAccount() {
        if (currentUserId == null) {
            return;
        }
        for (Friendship fr : getFriendships()) {
            friendshipRepository.delete(fr);
        }
        userRepository.delete(userRepository.findOne(currentUserId));
        ;
        currentUserId = null;
    }

    public String getIdCurent() {
        return currentUserId;
    }
    public User getCurrentUser() {
        return userRepository.findOne(currentUserId);
    }


    /**Metoda de parcurgere in adancime
     * @param start - nodul de la care se porneste parcurgerea
     * @param vizitat - vector cu pozitii pt fiecare camp din lista, care spune daca acesta a fost vizitat anterior sau nu
     */
    private void DFS(int start, boolean[] vizitat) {
        List<User> userList = userRepository.findAll();
        vizitat[start] = true;
        //System.out.println(visited[0]);
        for (Friendship f : friendshipRepository.findAll()) {
            //daca il gasim pe primul la un id din lista de prietenii si prietenul sau nu e vizitat
            if (f.getIdFriend1().equals(userList.get(start).getId()) && !vizitat[userList.indexOf(userRepository.findOne(f.getIdFriend2()))]) {

                dimComunitate++;

                //continuam cu cautarea prietenilor acelui prieten
                DFS(userList.indexOf(userRepository.findOne(f.getIdFriend2())), vizitat);
            }
            if (f.getIdFriend2().equals(userList.get(start).getId()) && !vizitat[userList.indexOf(userRepository.findOne(f.getIdFriend1()))]) {

                dimComunitate++;

                DFS(userList.indexOf(userRepository.findOne(f.getIdFriend1())), vizitat);
            }
        }
    }

    /**Metoda care da numarul de comunitati din reteaua noastra
     * @return nr de comunitati gasit*/
    public int nrComunitati() {
        List<User> lst = userRepository.findAll();

        int comunitati = 0;
        boolean[] vizitat = new boolean[lst.size()];
        for (int i = 0; i < lst.size(); i++) {
            vizitat[i] = false;
        }

        for (int i = 0; i < lst.size(); i++) {
            if (!vizitat[i]) {
                DFS(i, vizitat);
                comunitati++;
            }
        }

        return comunitati;
    }

    private int dimComunitate;

    /**Metoda care da cea mai sociabila comunitate(numarul ei de membrii)
     * @return nr de membrii ai acelei comunitati*/
    public List<String> ceaMaiSociabilaComunitate() {
        List<User> users = userRepository.findAll();

        int maxim = 0;
        int index=0;
        dimComunitate = 1;
        boolean[] visited = new boolean[users.size()];
        for (int i = 0; i < users.size(); i++) {
            visited[i] = false;
        }

        for (int i = 0; i < users.size(); i++) {
            if (!visited[i]) {
                DFS(i, visited);
                if(maxim<dimComunitate) {index=i; maxim=dimComunitate;}
                dimComunitate = 1;
            }
        }

        //afisare membrii
        for (int i = 0; i < users.size(); i++) {
            visited[i] = false;
        }
        DFS(index,visited);
        List<String> lst = new ArrayList<>(1);
        for(int i=0;i<users.size();i++){
            if(visited[i]){
                lst.add(userRepository.findAll().get(i).getId());
            }
        }
        return lst;
    }

    public void updateUser(String id, String firstName, String lastName, String password){
        User user = userRepository.findOne(id);
        if(user == null){
            throw new ValidationException("\n This user doens't exist!\n");
        }
        User newUser=new User(id, firstName, lastName, password);
        userRepository.update(user,newUser);
    }


    public Iterable<User> getAllUsers(){
        return userRepository.findAll();
    }

    @Override
    public void addObserver(Observer<FriendshipEntityChangeEvent> e) {
        observers.add(e);
    }

    @Override
    public void removeObserver(Observer<FriendshipEntityChangeEvent> e) {
        //observers.remove(e);
    }

    @Override
    public void notifyObservers(FriendshipEntityChangeEvent t) {
        observers.stream().forEach(x->x.update(t));
    }
}

