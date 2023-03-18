package socialnetwork.domain;

import java.io.Serial;
import java.util.Objects;
import java.util.UUID;

public class Entity<ID> {
    protected final ID id;

    /***
     * constructor
     */
    public Entity(ID id){
        if(id==null){
            this.id =  (ID) UUID.randomUUID().toString();
        }
        else{
            this.id=id;
        }
    }

    //getter id
    public ID getId() {
        return id;
    }

    /***
     * metoda suprascrisa equals
     * @param o - cel cu care comapram
     * @return true daca sunt egale, false altfe;
     */
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Entity entitate = (Entity) o;
        return Objects.equals(id, entitate.id);
    }

    /***
     * Metoda suprascrisa hashCode
     * @return hashCode
     */
    @Override
    public int hashCode() {
        return Objects.hash(id);
    }

    /***
     * Metoda suprascrisa toString
     * @return sirul corespunzator entitatii
     */
    @Override
    public String toString() {
        return "Entitate{" + "id='" + id + '\'' + '}';
    }

}