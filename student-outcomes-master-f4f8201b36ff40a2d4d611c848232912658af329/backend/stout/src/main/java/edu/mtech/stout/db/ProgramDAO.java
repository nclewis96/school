package edu.mtech.stout.db;

import edu.mtech.stout.core.Program;
import org.hibernate.SessionFactory;

import java.util.HashSet;
import java.util.List;
import java.util.Optional;

public class ProgramDAO extends StOutDAO<Program> {

  public ProgramDAO(SessionFactory factory) {
    super(factory);
  }


  public Optional<Program> findByName(String name) {
    List<Program> programList = list(namedQuery("edu.mtech.stout.core.Program.findByName")
      .setParameter(0, name));
    Optional<Program> user = Optional.empty();
    if (!programList.isEmpty()) {
      user = Optional.of(programList.get(0));
    }
    return user;
  }

  public List<Program> findByUser(Long userId) {
    return list(namedQuery("edu.mtech.stout.core.Program.findByUserId").setParameter(0, userId));
  }

  public List<Program> findByOfferingStudent(Long studentId, Long offeringId){
    return list(namedQuery("edu.mtech.stout.core.Program.findByStudent").setParameter(0, studentId).setParameter(1,offeringId));
  }

  public HashSet<Long> getProgramIdSetByUser(Long userId) {
    List<Program> programList = findByUser(userId);
    HashSet<Long> programSet = new HashSet<>();
    for (Program prog : programList) {
      programSet.add(prog.getId());
    }
    return programSet;
  }

  public List<Program> findByStudentAssign(Long studentId, Long assignId){
    return list(namedQuery("edu.mtech.stout.core.Program.findByStudentAssign").setParameter(0,studentId).setParameter(1,assignId));
  }
  public List<Program> findByStudentId(Long studentId){
    return list(namedQuery("edu.mtech.stout.core.Program.findByStudentId").setParameter(0,studentId));
  }

  public List<Program> findByOffering(Long offeringId){
    return list(namedQuery("edu.mtech.stout.core.Program.findByOffering").setParameter(0,offeringId));
  }

  public List<Program> findByMetric(Long metricId){
    return list(namedQuery("edu.mtech.stout.core.Program.findByMetric").setParameter(0, metricId));
  }

  public List<Program> findByPerformance(Long perfId){
    return list(namedQuery("edu.mtech.stout.core.Program.findByPerformance").setParameter(0,perfId));
  }

  public List<Program> findAll() {
    return list(namedQuery("edu.mtech.stout.core.Program.findAll"));
  }

}