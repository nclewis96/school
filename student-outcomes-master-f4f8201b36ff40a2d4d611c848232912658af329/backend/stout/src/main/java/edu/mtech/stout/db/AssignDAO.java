package edu.mtech.stout.db;

import edu.mtech.stout.core.Assign;
import org.hibernate.SessionFactory;

import java.util.List;
import java.util.Optional;

public class AssignDAO extends StOutDAO<Assign> {
  public AssignDAO(SessionFactory factory) {
    super(factory);
  }


  public Optional<Assign> findByCourse(long courseId) {
    List<Assign> assignList = list(namedQuery("edu.mtech.stout.core.Assign.findByCourse")
      .setParameter(0, courseId));
    Optional<Assign> assign = Optional.empty();
    if (!assignList.isEmpty()) {
      assign = Optional.of(assignList.get(0));
    }
    return assign;
  }

  public List<Assign> findProgramId(long programId){
    return list(namedQuery("edu.mtech.stout.core.Assign.findProgramId").setParameter(0,programId));
  }

  public List<Assign> findAll() {
    return list(namedQuery("edu.mtech.stout.core.Assign.findAll"));
  }
}
