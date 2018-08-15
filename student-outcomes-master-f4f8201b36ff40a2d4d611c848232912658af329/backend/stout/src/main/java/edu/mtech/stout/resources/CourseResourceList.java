package edu.mtech.stout.resources;

import edu.mtech.stout.api.QueryBySelector;
import edu.mtech.stout.core.Course;
import edu.mtech.stout.core.User;
import edu.mtech.stout.db.CourseDAO;
import edu.mtech.stout.db.ProgramDAO;
import edu.mtech.stout.db.UserDAO;
import io.dropwizard.auth.Auth;
import io.dropwizard.hibernate.UnitOfWork;
import io.dropwizard.jersey.params.LongParam;

import javax.annotation.security.RolesAllowed;
import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;
import java.util.List;

@Path("/courses")
@Produces(MediaType.APPLICATION_JSON)

public class CourseResourceList{
	private CourseDAO dao;
	private QueryBySelector queryBySelector = new QueryBySelector();

	public CourseResourceList(CourseDAO dao){
		this.dao = dao;

	}
	
	@POST
	@RolesAllowed({"Program Coordinator"})
	@UnitOfWork
	public Course createCourse(@Auth User user, Course course){
		if(queryBySelector.queryByProgramId(user, course.getProgramId())){
			return dao.create(course);
		}else{
			throw new NotAuthorizedException("Cannot create a Course not in your program");
		}

	}

	@GET
	@RolesAllowed({"Admin", "Program Coordinator", "Faculty"})
	@UnitOfWork
	public List<Course> getCourseList(@Auth User user, @QueryParam("programId") LongParam programId){
    if (queryBySelector.queryByProgramId(user, programId)) {
    	if(programId != null){
				return dao.findByProgramId(programId.get());
			}else {
				return dao.findAll();
			}

    } else {
    	throw new NotAuthorizedException("Cannot gget a Course not in your program");
    }

	}
}
