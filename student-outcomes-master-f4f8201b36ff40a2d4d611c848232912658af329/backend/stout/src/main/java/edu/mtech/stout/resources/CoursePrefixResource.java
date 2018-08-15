package edu.mtech.stout.resources;

import edu.mtech.stout.api.QueryBySelector;
import edu.mtech.stout.api.Status;
import edu.mtech.stout.core.Course;
import edu.mtech.stout.core.CoursePrefix;
import edu.mtech.stout.core.User;
import edu.mtech.stout.db.CourseDAO;
import edu.mtech.stout.db.CoursePrefixDAO;
import edu.mtech.stout.db.ProgramDAO;
import io.dropwizard.auth.Auth;
import io.dropwizard.hibernate.UnitOfWork;
import io.dropwizard.jersey.PATCH;
import io.dropwizard.jersey.params.LongParam;

import javax.annotation.security.RolesAllowed;
import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;
import java.util.List;

@Path("course-prefixes/{coursePrefixId}")
@Produces(MediaType.APPLICATION_JSON)
public class CoursePrefixResource {

  private CoursePrefixDAO dao;
  private QueryBySelector queryBySelector = new QueryBySelector();
  private CourseDAO courseDao;

  public CoursePrefixResource(CoursePrefixDAO dao, CourseDAO courseDao) {
    this.courseDao = courseDao;
    this.dao = dao;
  }

  @GET
  @UnitOfWork
  public CoursePrefix getCoursePrefix(@Auth User user, @PathParam("coursePrefixId") LongParam coursePrefixId) {
    //Checks to see if the User has access to the Course Prefix's Program
    List<Course> c = courseDao.findByCoursePrefixId(coursePrefixId.get());
    if(c.size() > 0){
      Boolean hasAccess = false;
      for(int i =0; i < c.size(); i++){
        if(queryBySelector.queryByProgramId(user, c.get(i).getId())){
          hasAccess = true;
        }
      }
      if(hasAccess){
        return findSafely(coursePrefixId.get());
      }else{
        throw new NotAuthorizedException("Cannot get Course Prefix not in your program");
      }
    }else{
      throw new NotFoundException("No Course Prefixes are available in your program.");
    }
  }

  private CoursePrefix findSafely(long coursePrefixId) {
    return dao.findById(coursePrefixId).orElseThrow(() -> new NotFoundException("No such Course Prefix"));
  }

  @PATCH
  @UnitOfWork
  public CoursePrefix updateCoursePrefix(@Auth User user, @PathParam("coursePrefixId") LongParam coursePrefixId, CoursePrefix coursePref) {
    //Checks to see if the User has access to the Course Prefix's Program
    List<Course> c = courseDao.findByCoursePrefixId(coursePrefixId.get());
    if(c.size() > 0){
      Boolean hasAccess = false;
      for(int i =0; i < c.size(); i++){
        if(queryBySelector.queryByProgramId(user, c.get(i).getId())){
          hasAccess = true;
        }
      }
      if(hasAccess){
        return dao.update(coursePref);
      }else{
        throw new NotAuthorizedException("Cannot update Course Prefix not in your program");
      }
    }else{
      throw new NotFoundException("No Course Prefixes are available in your program.");
    }
  }

  @DELETE
  @RolesAllowed({"Admin", "Program Coordinator"})
  @UnitOfWork
  public Status deleteCoursePrefix(@Auth User user, @PathParam("coursePrefixId") LongParam coursePrefixId) {
    //Checks to see if the User has access to the Course Prefix's Program
    List<Course> c = courseDao.findByCoursePrefixId(coursePrefixId.get());
    if(c.size() > 0){
      Boolean hasAccess = false;
      for(int i =0; i < c.size(); i++){
        if(queryBySelector.queryByProgramId(user, c.get(0).getId())){
          hasAccess = true;
        }
      }
      if(hasAccess){
        Status status = new Status();
        status.setId(coursePrefixId.get().intValue());
        status.setAction("DELETE");
        status.setResource("CoursePrefix");

        boolean success = dao.delete(findSafely(coursePrefixId.get().intValue()));

        if (success) {
          status.setMessage("Successfully deleted Course Prefix");
          status.setStatus(200);
        } else {
          status.setMessage("Error deleting course prefix");
          status.setStatus(500);
        }
        return status;
      }else{
        throw new NotAuthorizedException("Cannot delete Course Prefix not in your program");
      }
    }else{
      throw new NotFoundException("No Course Prefixes are available in your program.");
    }

  }
}