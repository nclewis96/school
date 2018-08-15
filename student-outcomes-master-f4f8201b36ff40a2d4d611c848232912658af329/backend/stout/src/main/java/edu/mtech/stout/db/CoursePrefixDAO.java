package edu.mtech.stout.db;

import edu.mtech.stout.core.CoursePrefix;
import org.hibernate.SessionFactory;

import java.util.List;

public class CoursePrefixDAO extends StOutDAO<CoursePrefix> {
  public CoursePrefixDAO(SessionFactory factory) {
    super(factory);
  }

  public List<CoursePrefix> findAll() {
    return list(namedQuery("edu.mtech.stout.core.CoursePrefix.findAll"));
  }

  public List<CoursePrefix> findByProgramId(Long programId) {
    return list(namedQuery("edu.mtech.stout.core.CoursePrefix.findByProgramId").setParameter(0, programId));
  }

  public List<CoursePrefix> findByUserId(Long userId){
    return list(namedQuery("edu.mtech.stout.core.CoursePrefix.findByUserId").setParameter(0,userId));
  }
}