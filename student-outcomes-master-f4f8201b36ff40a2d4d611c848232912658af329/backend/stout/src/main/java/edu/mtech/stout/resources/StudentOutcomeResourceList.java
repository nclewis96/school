package edu.mtech.stout.resources;

import edu.mtech.stout.api.QueryBySelector;
import edu.mtech.stout.core.Program;
import edu.mtech.stout.core.StudentOutcome;
import edu.mtech.stout.core.User;
import edu.mtech.stout.db.ProgramDAO;
import edu.mtech.stout.db.StudentOutcomeDAO;
import io.dropwizard.auth.Auth;
import io.dropwizard.hibernate.UnitOfWork;
import io.dropwizard.jersey.params.LongParam;

import javax.annotation.security.RolesAllowed;
import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;
import java.util.ArrayList;
import java.util.List;

@Path("/student-outcomes")
@Produces(MediaType.APPLICATION_JSON)
public class StudentOutcomeResourceList {

  private StudentOutcomeDAO dao;
  private ProgramDAO programDao;
  private QueryBySelector queryBySelector = new QueryBySelector();

  public StudentOutcomeResourceList(StudentOutcomeDAO dao, ProgramDAO programDao){
    this.programDao = programDao;
    this.dao = dao;
  }

  @POST
  @RolesAllowed({"Program Coordinator", "Faculty"})
  @UnitOfWork
  public StudentOutcome createStudentOutcome(@Auth User user, StudentOutcome studentOutcome) {
    List<Program> p = programDao.findByStudentId(studentOutcome.getStudentId());
    if(p.size()>0){
      Boolean hasAccess = false;
      for(int i =0; i < p.size(); i++){
        if(queryBySelector.queryByProgramId(user, p.get(i).getId())){
          hasAccess = true;
        }
      }
      if(hasAccess){
        return dao.create(studentOutcome);
      }else{
        throw new NotAuthorizedException("Cannot get a student not in your program");
      }
    }else{
      throw new NotFoundException("No Students are available with that Id");
    }

  }

  @GET
  @RolesAllowed({"Program Coordinator", "Faculty"})
  @UnitOfWork
  public List<StudentOutcome> getStudentOutcomeList(@Auth User user, @QueryParam("programId") LongParam programId){
    if(programId != null){
      if(queryBySelector.queryByProgramId(user,programId.get())){
        return dao.findByProgramId(programId.get());
      }else{
        throw new NotAuthorizedException("You do not have access to that program");
      }
    }else{
      ArrayList<StudentOutcome> fullList = new ArrayList<>();
      List<Program> programList = programDao.findByUser(user.getId());

      for(int i = 0; i < programList.size(); i++){
        List<StudentOutcome> tempList = dao.findByProgramId(programList.get(i).getId());
        for(int j = 0; j < tempList.size();j++){
          fullList.add(tempList.get(j));
        }
      }
      List<StudentOutcome> tempList = dao.findByUserId(user.getId());
      for(int i = 0; i < tempList.size(); i++){
        if(!fullList.contains(tempList.get(i))){
          fullList.add(tempList.get(i));
        }
      }
      return fullList;
    }
  }

}
