package edu.mtech.stout.resources;

import edu.mtech.stout.api.QueryBySelector;
import edu.mtech.stout.core.Course;
import edu.mtech.stout.core.OutcomeAssign;
import edu.mtech.stout.core.User;
import edu.mtech.stout.db.CourseDAO;
import edu.mtech.stout.db.OutcomeAssignDAO;
import edu.mtech.stout.db.ProgramDAO;
import io.dropwizard.auth.Auth;
import io.dropwizard.hibernate.UnitOfWork;
import io.dropwizard.jersey.params.LongParam;

import javax.annotation.security.RolesAllowed;
import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;
import java.awt.*;
import java.util.List;

@Path("/outcome-assigns")
@Produces(MediaType.APPLICATION_JSON)
public class OutcomeAssignResourceList {
  OutcomeAssignDAO dao;
  QueryBySelector queryBySelector = new QueryBySelector();
  CourseDAO courseDao;

  public OutcomeAssignResourceList(OutcomeAssignDAO dao, CourseDAO courseDao){
    this.dao = dao;
    this.courseDao = courseDao;
  }

  @POST
  @RolesAllowed({"Program Coordinator", "Faculty"})
  @UnitOfWork
  public OutcomeAssign createOutcomeAssign(@Auth User user, OutcomeAssign outcomeAssign){
    List<Course> c = courseDao.findByAssignId(outcomeAssign.getAssignId());
    if(c.size() > 0){
      Boolean hasAccess = false;
      for(int i = 0; i < c.size(); i++){
        if(queryBySelector.queryByProgramId(user, c.get(i).getProgramId())){
          hasAccess = true;
        }
      }
      if(hasAccess ){
        return  dao.create(outcomeAssign);
      }
      throw new NotAuthorizedException("Cannot create outcome assign not in your program");
    }else{
      throw new NotFoundException("No outcome assigns are available in your program.");
    }
  }

  @GET
  @RolesAllowed({"Program Coordinator", "Faculty"})
  @UnitOfWork
  public List<OutcomeAssign> getOutcomeAssignList(@Auth User user, @QueryParam("assignId")LongParam assignId) {
    if (assignId != null) {

      List<Course> c = courseDao.findByAssignId(assignId.get());
      if (c.size() > 0) {
        Boolean hasAccess = false;
        for (int i = 0; i < c.size(); i++) {
          if (queryBySelector.queryByProgramId(user, c.get(i).getProgramId())) {
            hasAccess = true;
          }
        }
        if (hasAccess) {
          return dao.findAll();
        }
        throw new NotAuthorizedException("Cannot get outcome assign not in your program");
      }

    }
    throw new NotFoundException("No outcome Assigns are available in your program");

  }
}
