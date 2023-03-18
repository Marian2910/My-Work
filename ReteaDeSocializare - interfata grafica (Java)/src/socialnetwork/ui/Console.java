package socialnetwork.ui;


import socialnetwork.domain.validators.ValidationException;
import socialnetwork.exceptions.DuplicateException;
import socialnetwork.service.UserService;
import java.util.InputMismatchException;
import java.util.Objects;
import java.util.Scanner;


public class Console implements Ui{

        public UserService userService;

        public Console(UserService userService){
            this.userService = userService;
        }
        public void runConsole(){
            Scanner input = new Scanner(System.in);

            while(true) {
                try {
                    System.out.println("Welcome, Log in/Sign up " +
                            "\nInsert 'l' for logging in or 's' for signing up. ('x' stops the app)" +
                            "\ncommand= \s");
                    String cmd = input.next();
                    if (Objects.equals(cmd, "l"))
                        runLoggingConsole();
                    else if (Objects.equals(cmd, "s"))
                        runSigningConsole();
                    else if (Objects.equals(cmd, "x"))
                        return;
                    else System.out.println("Invalid command!");
                }
            catch (Exception e) {
                System.out.println(e);
            }
            }

        }
        public void runSigningConsole(){
                System.out.println("Create an account: \n");
                addUser();
        }

        public void runLoggingConsole() {
            Scanner input = new Scanner(System.in);
            long username = 0;
            String password;
            System.out.println("Log in, insert username (id): \s");
            try {
                username = input.nextLong();
                System.out.println(userService.getOneUser(username).get().getFirstName() + " "+ userService.getOneUser(username).get().getLastName());
            } catch (Exception e) {
                System.out.println(e.getMessage());
            }

            if (userService.getOneUser(username).isPresent()) {
                System.out.println("Insert password: ");
                password = input.next();
                while(!Objects.equals(password, userService.getOneUser(username).get().getPassword())){
                    System.out.println("Invalid password!");
                    password = input.next();
                }
                if(Objects.equals(password, userService.getOneUser(username).get().getPassword()))
                    runUserConsole(username);

            }

        }

    private void runUserConsole(long username) {
            Scanner input = new Scanner(System.in);
            String  cmd = null;
            System.out.println("Welcome back, "+ userService.getOneUser(username).get().getFirstName()+"!");
            while(true){
                try{
                    showLoggingMenu();
                    cmd = input.next();}
                catch (Exception e){
                    System.out.println(e.getMessage());
                }
                if(Objects.equals(cmd, "1"))
                    updateUser(username);
                else if (Objects.equals(cmd, "2"))
                    makeFriend(username);
                else if (Objects.equals(cmd, "3"))
                    showUsers();
                else if (Objects.equals(cmd, "4"))
                    userService.displayFriends(username).forEach(System.out::println);
                else if(Objects.equals(cmd, "5"))
                    deleteFriend(username);
                else if(Objects.equals(cmd, "7")) {
                    deleteUser(username);
                    return;
                }
                else if(Objects.equals(cmd, "6"))
                    return;
                else System.out.println("Invalid command!");
            }


    }

    public void addUser() {
            long id;
            String firstName, lastName;

            System.out.print("ID: ");
            Scanner scan = new Scanner(System.in);
            try{
                id = scan.nextLong();
            } catch (InputMismatchException | DuplicateException e){
                System.out.println("🤦 Invalid ID!");
                return;
            }

            scan.nextLine();
            System.out.print("First name: ");
            firstName = scan.next();
            System.out.print("Last name: ");
            lastName = scan.next();
            System.out.println("Password: \n");
            String password = scan.next();
            System.out.println("Confirm password: \n");
            String password2 = scan.next();

            if(Objects.equals(password, password2)){
            try {
                userService.addUser(id, firstName, lastName, password);
            } catch (IllegalArgumentException | ValidationException  v){
                System.out.println(v.getMessage());
                return;
            }
            }

            else throw new ValidationException("🤦‍ The passwords are not the same!");

            System.out.println("\n Account successfully created 🤩!\n");
            runLoggingConsole();
        }

    public void updateUser(long id) {
        String cmd = null, newfirstName, newlastName;
        Scanner scan = new Scanner(System.in);
        while (true) {
            System.out.println("Choose what you want to update (name/password) and type 'ok' when finished: ");
            try {
                cmd = scan.next();
            } catch (Exception e) {
                System.out.println(e.getMessage());
            }
            if (Objects.equals(cmd, "name"))
                try {
                    System.out.print("First name: ");
                    newfirstName = scan.next();
                    System.out.print("Last name: ");
                    newlastName = scan.next();
                    userService.updateUser(id, newfirstName, newlastName, userService.getOneUser(id).get().getPassword());
                } catch (IllegalArgumentException | ValidationException e) {
                    System.out.println(e.getMessage());
                }
            else if (Objects.equals(cmd, "password"))
                try {
                    System.out.println("Insert current password: \n");
                    String password1 = scan.next();
                    if(Objects.equals(userService.getOneUser(id).get().getPassword(), password1)) {
                        System.out.println("Password: \n");
                        password1 = scan.next();
                        System.out.println("Confirm new password: \n");
                        String password2 = scan.next();
                        if (Objects.equals(password1, password2))
                            userService.updateUser(id, userService.getOneUser(id).get().getFirstName(), userService.getOneUser(id).get().getLastName(), password1);
                        else throw new IllegalArgumentException("🤦 Passwords do not match!");
                    }
                    else throw new IllegalArgumentException("🤦 Invalid password!");

                } catch (IllegalArgumentException | ValidationException  e) {
                    System.out.println(e.getMessage());

                }
            else if (Objects.equals(cmd, "ok"))
                return;
            else System.out.println("🤦 Invalid command!");}

    }
        public void deleteUser(long id){
             Scanner input = new Scanner (System.in);
             String answer;
             while(true) {
                 System.out.println("Are you sure you want to delete your account? 😢 -> (yes/no) ");
                 answer = input.next();
                 if (answer.equals("yes")) {
                     try {
                         this.userService.deleteAllFriends(id);
                         this.userService.deleteUser(id);
                         System.out.println("\n Account deleted successfully! 😔\n");
                         return;
                     } catch (ValidationException v) {
                         System.out.println(v.getMessage());
                     }
                 } else if (answer.equals("no")) {
                     System.out.println("\n The account has not been deleted! 😎\n");
                     runUserConsole(id);
                 }
                 else{ System.out.println("🤦‍ Invalid command");}
             }
        }

    public void showLoggingMenu(){
            System.out.println("1. Modify data \s" +
                    "2. Add a friend \s" +
                    "3. Show users \s" +
                    "4. Show friends \s" +
                    "5. Delete a friendship \s" +
                    "6. Log out \s" +
                    "7. Delete account \s");

    }

        public void showUsers(){
            userService.getAllUsers().forEach(System.out::println);
        }

        public void makeFriend(Long id){
            Scanner scan = new Scanner(System.in);
            System.out.print("Insert the user ID you want to become friend with: ");
            long idFriend;
            try{
                idFriend = scan.nextLong();
            }
            catch (InputMismatchException v) {
                System.out.println("\n🤦‍ ID not valid!\n");
                return;
            }

            try{
                this.userService.makeFriends(id, idFriend);;
            } catch(Exception v){
                System.out.println(v.getMessage());
                return;
            }

            System.out.println("\n 😎 You became friend with " + userService.getOneUser(idFriend).get().getFirstName()+" "+userService.getOneUser(idFriend).get().getLastName()+ ".\n");
        }

        public void deleteFriend(Long id){
            Scanner scan = new Scanner(System.in);
            System.out.print("The user id you want to delete from your friends list: ");
            Long idExFriend;
            try{
                idExFriend = scan.nextLong();
            }
            catch (InputMismatchException v) {
                System.out.println("\n🤦‍ Id not valid!\n");
                return;
            }

            try{
                this.userService.deleteFriend(id, idExFriend);
            }
            catch (Exception v){
                System.out.println(v.getMessage());
                return;
            }

            System.out.println("\n Friendship deleted successfully 😞 !\n");
        }
}
