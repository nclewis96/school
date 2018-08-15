package edu.mtech.stout.resources;

import edu.mtech.stout.api.QueryBySelector;
import edu.mtech.stout.core.Course;
import edu.mtech.stout.core.CoursePrefix;
import edu.mtech.stout.core.Program;
import edu.mtech.stout.core.User;
import edu.mtech.stout.db.CourseDAO;
import edu.mtech.stout.db.CoursePrefixDAO;
import edu.mtech.stout.db.ProgramDAO;
import io.dropwizard.auth.Auth;
import io.dropwizard.hibernate.UnitOfWork;
import io.dropwizard.jersey.params.LongParam;

import javax.annotation.security.RolesAllowed;
import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;
import java.util.ArrayList;
import java.util.List;

@Path("/course-prefixes")
@Produces(MediaType.APPLICATION_JSON)
public class CoursePrefixResourceList {

  private CoursePrefixDAO dao;
  private QueryBySelector queryBySelector = new QueryBySelector();
  private CourseDAO courseDao;
  private ProgramDAO programDao;

  public CoursePrefixResourceList(CoursePrefixDAO dao, ProgramDAO programDao, CourseDAO courseDao ) {
    this.courseDao = courseDao;
    this.dao = dao;
    this.programDao = programDao;
  }

  @POST
  @RolesAllowed({"Admin", "Program Coordinator"})
  @UnitOfWork
  public CoursePrefix createCoursePrefix(@Auth User user, CoursePrefix coursePrefix) {
    //Checks to see if the User has access to the Course Prefix's Program
    List<Course> c = courseDao.findByCoursePrefixId(coursePrefix.getId());
    if(c.size() > 0){
      Boolean hasAccess = false;
      for(int i =0; i < c.size(); i++){
        if(queryBySelector.queryByProgramId(user, c.get(i).getId())){
          hasAccess = true;
        }
      }
      if(hasAccess){
        return dao.create(coursePrefix);
      }else{
        throw new NotAuthorizedException("Cannot create Course Prefix not in your program");
      }
    }else{
      throw new NotFoundException("No Course Prefixes are available in your program.");
    }
  }

  @GET
  @RolesAllowed({"Program Coordinator", "Faculty"})
  @UnitOfWork
  public List<CoursePrefix> getCoursePrefixList(@Auth User user, @QueryParam("programId") LongParam programId) {
    //Checks to see if the User has access to the ProgramID, if no programID
    //return all the stuff from the programs the User has access to
    if(programId != null){
      if(queryBySelector.queryByProgramId(user, programId.get()) ){
        return dao.findByProgramId(programId.get());
      }else{
        throw new NotAuthorizedException("Cannot get Course Prefixes not in your program");
      }
    }else{
      //If no Query Params, return all Course Prefix the user has access to.
      ArrayList<CoursePrefix> fullList = new ArrayList<>();
      List<Program> programList = programDao.findByUser(user.getId());

      for(int i = 0; i < programList.size(); i++){
        List<CoursePrefix> tempList = dao.findByProgramId(programList.get(i).getId());
        for(int j = 0; j < tempList.size(); j++){
          fullList.add(tempList.get(j));
        }
      }

      List<CoursePrefix> tempList = dao.findByUserId(user.getId());
      for(int i = 0; i < tempList.size();i++){
        if(!fullList.contains(tempList.get(i))){
          fullList.add(tempList.get(i));
        }
      }

      return fullList;
    }
  }

}