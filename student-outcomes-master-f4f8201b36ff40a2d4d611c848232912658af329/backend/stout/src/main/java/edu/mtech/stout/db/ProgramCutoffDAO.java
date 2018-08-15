package edu.mtech.stout.db;

import edu.mtech.stout.core.Program;
import edu.mtech.stout.core.ProgramCutoff;
import org.hibernate.SessionFactory;

import java.util.List;

public class ProgramCutoffDAO extends StOutDAO<ProgramCutoff>{

  public ProgramCutoffDAO(SessionFactory factory){
    super(factory);
  }

  public List<ProgramCutoff> findAll(){
    return list(namedQuery("edu.mtech.stout.core.ProgramCutoff.findAll"));
  }

  public List<ProgramCutoff> findByProgram(Long programId){
    return list(namedQuery("edu.mtech.stout.core.ProgramCutoff.findByProgram").setParameter(0,programId));
  }
}
