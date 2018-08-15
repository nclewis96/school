package edu.mtech.stout.db;

import io.dropwizard.hibernate.AbstractDAO;
import org.hibernate.SessionFactory;

import java.io.Serializable;
import java.util.Optional;

public class StOutDAO<Type extends Serializable> extends AbstractDAO<Type> {

  public StOutDAO(SessionFactory factory) {
    super(factory);
  }

  public Optional<Type> findById(Long id) {
    return Optional.ofNullable(get(id));
  }

  public Optional<Type> findById(Type id) {return Optional.ofNullable(get(id)); }

  public Type create(Type type) {
    return persist(type);
  }

  public Type update(Type type) {
    return persist(type);
  }

  public boolean delete(Type type) {
    currentSession().delete(type);
    return true;
  }
}
