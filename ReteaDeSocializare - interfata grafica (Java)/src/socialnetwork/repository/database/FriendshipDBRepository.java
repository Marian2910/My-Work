package socialnetwork.repository.database;


import socialnetwork.domain.Friendship;
import socialnetwork.domain.User;
import socialnetwork.repository.Repository;

import java.sql.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class FriendshipDBRepository implements Repository<String, Friendship> {
    private final String url;
    private final String username;
    private final String password;

    public FriendshipDBRepository(String url, String username, String password) {
        this.url = url;
        this.username = username;
        this.password = password;
    }

    @Override
    public User findOne(String id) {
        String sql = "select * from \"Friendships\" where id = ? ";
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement ps = connection.prepareStatement(sql)) {

            ps.setString(1, id);
            ResultSet resultSet = ps.executeQuery();

            DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm");

            while(resultSet.next()){
                String idFriend1 = resultSet.getString("idprieten1");
                String idFriend2 = resultSet.getString("idprieten2");
                LocalDateTime data = LocalDateTime.parse(resultSet.getString("data"),formatter);
                Boolean pending = resultSet.getBoolean("status");
                return Optional.of(new Friendship(id, idFriend1, idFriend2, data, pending));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return null;
    }

    @Override
    public List<Friendship> findAll() {
        List<Friendship> friendships = new ArrayList<>();
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement("SELECT * from \"Friendships\"");
             ResultSet resultSet = statement.executeQuery()) {

            while (resultSet.next()) {
                String id = resultSet.getString("id");
                String idFriend1 = resultSet.getString("idFriend1");
                String idFriend2 = resultSet.getString("idFriend2");
                String data = resultSet.getString("data");

                DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm");
                LocalDateTime dateTime = LocalDateTime.parse(data, formatter);

                Boolean pending = resultSet.getBoolean("status");

                Friendship friendship = new Friendship(id, idFriend1, idFriend2, dateTime,pending);
                friendships.add(friendship);
            }
            return friendships;
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return friendships;
    }

    @Override
    public void save(Friendship friendship) {
        String sql = "insert into \"Friendships\" (id,idprieten1,idprieten2,data,status) values (?,?,?,?,?)";

        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement ps = connection.prepareStatement(sql)) {

            ps.setString(1, friendship.getId());
            ps.setString(2, friendship.getIdFriend1());
            ps.setString(3, friendship.getIdFriend2());

            DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm");
            String data=friendship.getData().format(formatter);

            ps.setString(4, data);
            ps.setBoolean(5, friendship.getPending());

            ps.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void delete(Friendship friendship) {
        String sql = "delete from \"Friendships\" where id = ?";
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement ps = connection.prepareStatement(sql)) {

            ps.setString(1, friendship.getId());
            ps.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void update(Friendship oldEntity, Friendship newEntity) {
        String sql = "update \"Friendships\" set idprieten1 = ?, idprieten2 = ?, data = ?, status = ? where id = ?";
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement ps = connection.prepareStatement(sql)) {

            ps.setString(1,newEntity.getIdFriend1());
            ps.setString(2, oldEntity.getIdFriend2());

            DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm");
            String data=newEntity.getData().format(formatter);

            ps.setString(3, data);
            ps.setBoolean(4, newEntity.getPending());
            ps.setString(5, oldEntity.getId());

            ps.executeUpdate();

        }catch(SQLException e){
            e.printStackTrace();
        }

    }
}
