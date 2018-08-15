package edu.mtech.stout.db;

import edu.mtech.stout.core.OutcomeAssign;
import org.hibernate.SessionFactory;

import java.util.List;

public class OutcomeAssignDAO extends  StOutDAO<OutcomeAssign>{

  public OutcomeAssignDAO(SessionFactory factory) {
    super(factory);
  }

  public List<OutcomeAssign> findAll(){
    return list(namedQuery("edu.mtech.stout.core.OutcomeAssign.findAll"));
  }
}
