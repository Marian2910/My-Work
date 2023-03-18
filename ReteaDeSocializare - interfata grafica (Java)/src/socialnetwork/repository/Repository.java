package socialnetwork.repository;

import socialnetwork.domain.Entity;
import socialnetwork.domain.User;
import socialnetwork.domain.validators.ValidationException;

import java.util.List;

/**
 * CRUD operations repository interface
 * @param <ID> - type E must have an attribute of type ID
 * @param <E> -  type of entities saved in repository
 */

public interface Repository<ID, E extends Entity<ID>> {

    /**
     * @param id -the id of the entity to be returned
     *           id must not be null
     * @return an {@code Optional} encapsulating the entity with the given id
     * @throws IllegalArgumentException if id is null.
     */
    E findOne(ID id);

    /**
     * @return all entities
     */
    List<E> findAll();

    /**
     * @param entity entity must be not null
     * @throws ValidationException      if the entity is not valid
     * @throws IllegalArgumentException if the given entity is null.     *
     */
    void save(E entity);


    /**
     *
     * @param entity
     */
    void delete(E entity);

    ;

    /**
     * @param oldEntity
     * @param newEntity
     */
    void update(E oldEntity, E newEntity);


}