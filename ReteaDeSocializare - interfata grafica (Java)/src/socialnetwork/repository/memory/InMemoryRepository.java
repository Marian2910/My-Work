package socialnetwork.repository.memory;

import socialnetwork.domain.Entity;
import socialnetwork.domain.User;
import socialnetwork.domain.validators.Validator;
import socialnetwork.repository.Repository;
import socialnetwork.exceptions.ValidationException;


import java.util.*;

public class InMemoryRepository<ID, E extends Entity<ID>> implements Repository<ID,E> {

    private final Validator<E> validator;
    Map<ID,E> entities;

    public InMemoryRepository(Validator<E> validator) {
        this.validator = validator;
        entities=new HashMap<ID,E>();
    }


    @Override
    public User findOne(ID id) {
        if (id == null) {
            throw new IllegalArgumentException("id must not be null");
        }
        return Optional.ofNullable(entities.get(id));
    }

    @Override
    public List<E> findAll() {
        return entities.values().stream().toList();
    }

    @Override
    public void save(E entity)  {
        if(entities == null)
            throw new IllegalArgumentException("Entity can't be null!");
        if(entities.get(entity.getId()) != null)
            throw new IllegalArgumentException("There is already an user with this id!");
        else {
            this.validator.validate(entity);
            entities.putIfAbsent(entity.getId(), entity);
            }
    }

    @Override
    public void delete(ID id) {
        if(entities.containsKey(id)){
            entities.remove(id);
        }
        else{
            throw new ValidationException("User not found!");
        }
    }

    @Override
    public void update(E entity)  {
        if (entity == null) {
            throw new IllegalArgumentException("Entity must not be null");
        }
        validator.validate(entity);
        entities.computeIfPresent(entity.getId(), (k, v) -> entity);
    }

}
