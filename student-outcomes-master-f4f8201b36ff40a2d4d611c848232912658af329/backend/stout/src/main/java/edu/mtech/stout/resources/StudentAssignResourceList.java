package edu.mtech.stout.resources;

import edu.mtech.stout.api.QueryBySelector;
import edu.mtech.stout.core.Program;
import edu.mtech.stout.core.StudentAssign;
import edu.mtech.stout.core.User;
import edu.mtech.stout.db.ProgramDAO;
import edu.mtech.stout.db.StudentAssignDAO;
import io.dropwizard.auth.Auth;
import io.dropwizard.hibernate.UnitOfWork;
import io.dropwizard.jersey.params.LongParam;

import javax.annotation.security.RolesAllowed;
import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;
import java.awt.*;
import java.util.ArrayList;
import java.util.List;

@Path("/student-assigns")
@Produces(MediaType.APPLICATION_JSON)
public class StudentAssignResourceList {

  private StudentAssignDAO dao;
  private ProgramDAO programDao;
  private QueryBySelector queryBySelector = new QueryBySelector();

  public StudentAssignResourceList(StudentAssignDAO dao, ProgramDAO programDao){
    this.dao = dao;
    this.programDao = programDao;
  }

  @POST
  @RolesAllowed({"Program Coordinator", "Faculty"})
  @UnitOfWork
  public StudentAssign createStudentAssign(@Auth User user, StudentAssign studentAssign) {
    List<Program> p = programDao.findByStudentAssign(studentAssign.getStudentId(), studentAssign.getAssignId());
    if(p.size()>0){
      Boolean hasAccess = false;
      for(int i =0; i < p.size(); i++){
        if(queryBySelector.queryByProgramId(user, p.get(i).getId())){
          hasAccess = true;
        }
      }
      if(hasAccess){
        return dao.create(studentAssign);
      }else{
        throw new NotAuthorizedException("Cannot create a student not in your program");
      }
    }else{
      throw new NotFoundException("StudentId is not associated with a program");
    }
  }

  @PUT
  @RolesAllowed({"Admin", "Program Coordinator"})
  @UnitOfWork
  public List<StudentAssign> setAssigns(@Auth User user, List<StudentAssign> assigns) {
    ArrayList<Program> fullList = new ArrayList<>();
    for(int i = 0; i < assigns.size(); i++){
       List<Program> p = programDao.findByStudentAssign(assigns.get(i).getStudentId(), assigns.get(i).getAssignId());
       for(int j = 0; j < p.size(); j++){
         fullList.add(p.get(i));
       }
    }
    if(fullList.size()>0){
      Boolean hasAccess = false;
      for(int i =0; i < fullList.size(); i++){
        if(queryBySelector.queryByProgramId(user, fullList.get(i).getId())){
          hasAccess = true;
        }
      }
      if(hasAccess){
        ArrayList<StudentAssign> newAssigns = new ArrayList<>();
        for(StudentAssign assign : assigns){
          if(dao.findById(assign).isPresent()){
            newAssigns.add(dao.update(assign));
          }else {
            newAssigns.add(dao.create(assign));
          }
        }
        return newAssigns;
      }else{
        throw new NotAuthorizedException("Cannot create a student(s) not in your program");
      }
    }else{
      throw new NotFoundException("StudentId is not associated with a program");
    }

  }

  @GET
  @RolesAllowed({"Program Coordinator", "Faculty"})
  @UnitOfWork
  public List<StudentAssign> getStudentAssignList(@Auth User user, @QueryParam("programId") LongParam programId){
    if(programId != null){
      if(queryBySelector.queryByProgramId(user, programId.get())){
        return dao.findByProgramId(programId.get());
      }else{
        throw new NotAuthorizedException("Cannot get student assignments not in your program");
      }
    }else{
      ArrayList<StudentAssign> fullList = new ArrayList<>();
      List<Program> programList = programDao.findByUser(user.getId());

      for(int i = 0; i < programList.size(); i++){
        List<StudentAssign> tempList = dao.findByProgramId(programList.get(i).getId());
        for(int j = 0; j < tempList.size();j++){
          fullList.add(tempList.get(j));
        }
      }
      List<StudentAssign> tempList = dao.findByUserId(user.getId());
      for(int i = 0; i < tempList.size(); i++){
        if(!fullList.contains(tempList.get(i))){
          fullList.add(tempList.get(i));
        }
      }
      return fullList;
    }
  }
}
