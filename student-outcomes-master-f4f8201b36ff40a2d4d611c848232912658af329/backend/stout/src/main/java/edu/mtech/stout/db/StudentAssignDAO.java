package edu.mtech.stout.db;

import edu.mtech.stout.core.StudentAssign;
import org.hibernate.SessionFactory;

import java.util.List;

public class StudentAssignDAO extends StOutDAO<StudentAssign>{

  public StudentAssignDAO(SessionFactory factory){ super(factory);}

  public List<StudentAssign> findByUserId(Long userId){
    return list(namedQuery("edu.mtech.stout.core.StudentAssign.findByUserId").setParameter(0,userId));
  }

  public List<StudentAssign> findByProgramId(Long programId){
    return list(namedQuery("edu.mtech.stout.core.StudentAssign.findByProgramId").setParameter(0, programId));
  }

  public List<StudentAssign> findAll(){ return list(namedQuery("edu.mtech.stout.core.StudentAssign.findAll"));}


}
