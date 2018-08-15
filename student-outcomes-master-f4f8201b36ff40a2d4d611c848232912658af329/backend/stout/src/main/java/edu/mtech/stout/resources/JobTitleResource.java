package edu.mtech.stout.resources;

import edu.mtech.stout.api.Status;
import edu.mtech.stout.core.JobTitle;
import edu.mtech.stout.db.JobTitleDAO;
import io.dropwizard.hibernate.UnitOfWork;
import io.dropwizard.jersey.PATCH;
import io.dropwizard.jersey.params.LongParam;

import javax.annotation.security.PermitAll;
import javax.annotation.security.RolesAllowed;
import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;

@Path("/job-titles/{jobTitleId}")
@Produces(MediaType.APPLICATION_JSON)
public class JobTitleResource {

  private JobTitleDAO dao;

  public JobTitleResource(JobTitleDAO dao){
    this.dao = dao;
  }

  @GET
  @RolesAllowed({"Amdin", "Program Coordinator", "Faculty"})
  @UnitOfWork
  public JobTitle getJobTitle(@PathParam("jobTitleId") LongParam jobtitleId){return findSafely(jobtitleId.get());}

  private JobTitle findSafely(long jobTitleId){
    return dao.findById(jobTitleId).orElseThrow(() -> new NotFoundException("No such Job Title"));
  }

  @PATCH
  @RolesAllowed({"Admin"})
  @UnitOfWork
  public JobTitle updateJobTitle(@PathParam("jobTitleId") LongParam jobTitleId, JobTitle jobTitle){
   return dao.update(jobTitle);
  }

  @DELETE
  @RolesAllowed({"Admin"})
  @UnitOfWork
  public Status deleteJobTitle(@PathParam("jobTitleId") LongParam jobTitleId) {
    Status status = new Status();
    status.setId(jobTitleId.get().intValue());
    status.setAction("DELETE");
    status.setResource("JobTitle");

    boolean success = dao.delete(findSafely(jobTitleId.get().intValue()));

    if (success) {
      status.setMessage("Successfully deleted Job Title");
      status.setStatus(200);
    } else {
      status.setMessage("Error deleting Job Title");
      status.setStatus(500);
    }

    return status;

  }

}
