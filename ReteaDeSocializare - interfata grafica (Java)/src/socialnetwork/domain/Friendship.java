package socialnetwork.domain;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.Objects;

public class Friendship extends Entity<String>{
    private final String idFriend1, idFriend2;
    private LocalDateTime data;
    private Boolean pending = true;

    /***
     * constructor
     * @param id
     * @param idFriend1
     * @param idFriend2
     */
    public Friendship(String id, String idFriend1, String idFriend2, LocalDateTime data, Boolean pending){
        super(id);
        this.idFriend1 =idFriend1;
        this.idFriend2 =idFriend2;
        this.data=data;
        this.pending=pending;
    }
    public Friendship(String id, String idPrieten1, String idPrieten2){
        super(id);
        this.idFriend1 =idPrieten1;
        this.idFriend2 =idPrieten2;
        this.data=LocalDateTime.now();
        this.pending=pending;
    }
    public Friendship(String id, String idPrieten1, String idPrieten2, LocalDateTime data){
        super(id);
        this.idFriend1 =idPrieten1;
        this.idFriend2 =idPrieten2;
        this.data=data;
        this.pending=pending;
    }
    public Friendship(String id, String idPrieten1, String idPrieten2, Boolean pending){
        super(id);
        this.idFriend1 =idPrieten1;
        this.idFriend2 =idPrieten2;
        this.data=LocalDateTime.now();
        this.pending=pending;
    }


    @Override
    public String toString() {
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm");
        String dataFormatata=data.format(formatter);
        return "Friendship{" +
                "idFriend1='" + idFriend1 + '\'' +
                ", idFriend2='" + idFriend2 + '\'' +
                ", date=" + dataFormatata +
                ", id=" + id +
                '}';
    }
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        if (!super.equals(o)) return false;
        Friendship prietenie = (Friendship) o;
        return Objects.equals(idFriend1, prietenie.idFriend1) && Objects.equals(idFriend2, prietenie.idFriend2) && Objects.equals(data, prietenie.data);
    }

    @Override
    public int hashCode() {
        return Objects.hash(super.hashCode(), idFriend1, idFriend2, data);
    }

    /***
     * Getter id prieten 1 (settere nu am ca s finale)
     * @return id prieten 1
     */
    public String getIdFriend1() {
        return idFriend1;
    }
    /***
     * Getter id prieten 2 (settere nu am ca s finale)
     * @return id prieten 2
     */
    public String getIdFriend2() {
        return idFriend2;
    }

    public LocalDateTime getData() {return data;}

    public void setData(LocalDateTime data) {
        this.data = data;
    }

    public Boolean getPending() {
        return pending;
    }

    public void setPending(Boolean pending) {
        this.pending = pending;
    }
}
