package edu.mtech.stout.resources;


import edu.mtech.stout.core.JobTitle;
import edu.mtech.stout.core.User;
import edu.mtech.stout.db.JobTitleDAO;
import io.dropwizard.auth.Auth;
import io.dropwizard.hibernate.UnitOfWork;
import io.dropwizard.jersey.params.LongParam;

import javax.annotation.security.RolesAllowed;
import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;
import java.util.List;

@Path("/job-titles")
@Produces(MediaType.APPLICATION_JSON)
public class JobTitleResourceList {

  private JobTitleDAO dao;

  public JobTitleResourceList(JobTitleDAO dao){
    this.dao = dao;
  }

  @POST
  @RolesAllowed({"Admin"})
  @UnitOfWork
  public JobTitle createJobTitle(JobTitle jobTitle) { return dao.create(jobTitle);}

  @GET
  @RolesAllowed({"Amdin", "Program Coordinator", "Faculty"})
  @UnitOfWork
  public List<JobTitle> getJobTitleList(@Auth User user, @QueryParam("userId") LongParam userId){
    if(userId != null){
      return dao.getByUserId(userId.get());
    }else{
      return  dao.findAll();
    }
  }

}
