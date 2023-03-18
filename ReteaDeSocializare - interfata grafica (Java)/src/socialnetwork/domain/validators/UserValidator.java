package socialnetwork.domain.validators;

import org.jetbrains.annotations.NotNull;
import socialnetwork.domain.User;

public class UserValidator implements Validator<User> {
    @Override
    public void validate(User utilizator) throws ValidationException {
        String errors = "";
        if(utilizator.getFirstName().isEmpty()){
                errors += "FirstName can't be empty.\n";
            }
            if(utilizator.getLastName().isEmpty()){
                errors += "LastName can't be empty.\n";
            }

            boolean fname = utilizator.getFirstName().chars().allMatch(Character::isLetter);
            if(!fname){
                errors += "FirstName must not contain numbers.\n";
            }
            boolean lname = utilizator.getLastName().chars().allMatch(Character::isLetter);
            if(!lname){
                errors += "LastName must not contain numbers.\n";
            }
            if(errors.length()>0)
                throw new ValidationException("\n" + errors);
        }
}