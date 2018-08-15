package edu.mtech.stout.db;

import edu.mtech.stout.core.StudentOutcome;
import org.hibernate.SessionFactory;

import java.util.List;

public class StudentOutcomeDAO extends StOutDAO<StudentOutcome> {

  public StudentOutcomeDAO(SessionFactory factory){ super(factory);}

  public List<StudentOutcome> findAll(){
    return list(namedQuery("edu.mtech.stout.core.StudentOutcome.findAll"));
  }

  public List<StudentOutcome> findByProgramId(Long programId){
    return list(namedQuery("edu.mtech.stout.core.StudentOutcome.findByProgramId").setParameter(0,programId));
  }

  public List<StudentOutcome> findByUserId(Long userId){
    return list(namedQuery("edu.mtech.stout.core.StudentOutcome.findByUserId").setParameter(0,userId));
  }
}
