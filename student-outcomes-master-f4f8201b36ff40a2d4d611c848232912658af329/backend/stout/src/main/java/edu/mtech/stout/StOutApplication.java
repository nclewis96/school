package edu.mtech.stout;

import edu.mtech.stout.api.AuthenticationObject;
import edu.mtech.stout.api.QueryBySelector;
import edu.mtech.stout.auth.StOutAuthenticator;
import edu.mtech.stout.auth.StOutAuthorizer;
import edu.mtech.stout.client.CASValidator;
import edu.mtech.stout.core.*;
import edu.mtech.stout.db.*;
import edu.mtech.stout.filter.UserAuthFilter;
import edu.mtech.stout.resources.*;
import io.dropwizard.Application;
import io.dropwizard.assets.AssetsBundle;
import io.dropwizard.auth.AuthDynamicFeature;
import io.dropwizard.auth.AuthValueFactoryProvider;
import io.dropwizard.client.JerseyClientBuilder;
import io.dropwizard.configuration.EnvironmentVariableSubstitutor;
import io.dropwizard.configuration.SubstitutingSourceProvider;
import io.dropwizard.db.DataSourceFactory;
import io.dropwizard.hibernate.HibernateBundle;
import io.dropwizard.hibernate.UnitOfWorkAwareProxyFactory;
import io.dropwizard.setup.Bootstrap;
import io.dropwizard.setup.Environment;
import io.dropwizard.sslreload.SslReloadBundle;
import org.eclipse.jetty.servlets.CrossOriginFilter;
import org.glassfish.jersey.server.filter.RolesAllowedDynamicFeature;

import javax.servlet.DispatcherType;
import javax.servlet.FilterRegistration;
import javax.ws.rs.client.Client;
import java.util.EnumSet;

public class StOutApplication extends Application<StOutConfiguration> {

  public static void main(final String[] args) throws Exception {
    new StOutApplication().run(args);
  }

  private final HibernateBundle<StOutConfiguration> hibernateBundle =
    new HibernateBundle<StOutConfiguration>(User.class, Role.class, Assign.class,
      Metric.class, Offering.class, Outcome.class, Program.class,
      Scale.class, Semester.class, Course.class, JobTitle.class,
      CoursePrefix.class, Permissions.class, Performance.class,
        StudentAssign.class, CourseOutcome.class, OfferingOutcome.class,
        SemesterType.class, ProgramCutoff.class, OutcomeAssign.class,
        StudentOutcome.class, OfferingStudent.class) {

      @Override
      public DataSourceFactory getDataSourceFactory(StOutConfiguration configuration) {
        return configuration.getDataSourceFactory();
      }
    };

  @Override
  public String getName() {
    return "StOut";
  }

  @Override
  public void initialize(final Bootstrap<StOutConfiguration> bootstrap) {
    // Enable variable substitution with environment variables
    bootstrap.setConfigurationSourceProvider(
      new SubstitutingSourceProvider(
        bootstrap.getConfigurationSourceProvider(),
        new EnvironmentVariableSubstitutor(false)
      )
    );
    bootstrap.addBundle(new AssetsBundle());
    bootstrap.addBundle(hibernateBundle);
    bootstrap.addBundle(new SslReloadBundle());
  }

  @Override
  public void run(final StOutConfiguration configuration,
                  final Environment environment) {

    // Enable CORS headers
    final FilterRegistration.Dynamic cors =
      environment.servlets().addFilter("CORS", CrossOriginFilter.class);

    // Configure CORS parameters
    cors.setInitParameter("allowedOrigins", "*");
    cors.setInitParameter("allowedHeaders", "X-Requested-With,Content-Type,Accept,Origin, Authorization");
    cors.setInitParameter("allowedMethods", "OPTIONS,GET,PUT,POST,PATCH,DELETE,HEAD");

    // Add URL mapping
    cors.addMappingForUrlPatterns(EnumSet.allOf(DispatcherType.class), true, "/*");

    // DO NOT pass a preflight request to down-stream auth filters
    // unauthenticated preflight requests should be permitted by spec
    cors.setInitParameter(CrossOriginFilter.CHAIN_PREFLIGHT_PARAM, Boolean.FALSE.toString());

    //Set up DAO objects
    final AssignDAO assignDao = new AssignDAO(hibernateBundle.getSessionFactory());
    final UserDAO userDao = new UserDAO(hibernateBundle.getSessionFactory());
    final ProgramDAO programDao = new ProgramDAO(hibernateBundle.getSessionFactory());
    final OfferingDAO offeringDao = new OfferingDAO(hibernateBundle.getSessionFactory());
    final OutcomeDAO outcomeDao = new OutcomeDAO(hibernateBundle.getSessionFactory());
    final MetricDAO metricDao = new MetricDAO(hibernateBundle.getSessionFactory());
    final ScaleDAO scaleDao = new ScaleDAO(hibernateBundle.getSessionFactory());
    final SemesterDAO semesterDao = new SemesterDAO(hibernateBundle.getSessionFactory());
    final RoleDAO roleDao = new RoleDAO(hibernateBundle.getSessionFactory());
    final CourseDAO courseDao = new CourseDAO(hibernateBundle.getSessionFactory());
    final JobTitleDAO jobTitleDAO = new JobTitleDAO(hibernateBundle.getSessionFactory());
    final CoursePrefixDAO courseprefixDAO = new CoursePrefixDAO(hibernateBundle.getSessionFactory());
    final PermissionsDAO permissionsDAO = new PermissionsDAO(hibernateBundle.getSessionFactory());
    final PerformanceDAO performanceDAO = new PerformanceDAO(hibernateBundle.getSessionFactory());
    final StudentAssignDAO studentAssignDAO = new StudentAssignDAO(hibernateBundle.getSessionFactory());
    final CourseOutcomeDAO courseOutcomeDAO = new CourseOutcomeDAO(hibernateBundle.getSessionFactory());
    final OfferingOutcomeDAO offeringOutcomeDAO = new OfferingOutcomeDAO(hibernateBundle.getSessionFactory());
    final SemesterTypeDAO semesterTypeDAO = new SemesterTypeDAO(hibernateBundle.getSessionFactory());
    final ProgramCutoffDAO programCutoffDAO = new ProgramCutoffDAO(hibernateBundle.getSessionFactory());
    final StudentOutcomeDAO studentOutcomeDAO = new StudentOutcomeDAO(hibernateBundle.getSessionFactory());
    final OutcomeAssignDAO outcomeAssignDAO = new OutcomeAssignDAO(hibernateBundle.getSessionFactory());
    final OfferingStudentDAO offeringStudentDao = new OfferingStudentDAO(hibernateBundle.getSessionFactory());

    //Set up auth
    StOutAuthenticator stOutAuthenticator = new UnitOfWorkAwareProxyFactory(hibernateBundle)
      .create(StOutAuthenticator.class, UserDAO.class, userDao);
    StOutAuthorizer stOutAuthorizer = new UnitOfWorkAwareProxyFactory(hibernateBundle)
      .create(StOutAuthorizer.class, RoleDAO.class, roleDao);
    environment.jersey().register(new AuthDynamicFeature(
      new UserAuthFilter.Builder<User>()
        .setAuthenticator(stOutAuthenticator)
        .setAuthorizer(stOutAuthorizer)
        .setPrefix("Bearer")
        .buildAuthFilter()));
    environment.jersey().register(RolesAllowedDynamicFeature.class);
    environment.jersey().register(new AuthValueFactoryProvider.Binder<>(User.class));
    final Client client = new JerseyClientBuilder(environment).using(configuration.getJerseyClientConfiguration()).build(getName());
    CASValidator cas = new CASValidator(configuration, client);
    environment.jersey().register(cas);
    environment.jersey().register(new Login(cas, userDao, roleDao, jobTitleDAO));
    AuthenticationObject.setSecret(configuration.getJwtSecret());
    AuthenticationObject.setService(configuration.getService());

    //Set up routes
    environment.jersey().register(new UserResource(userDao, jobTitleDAO, roleDao));
    environment.jersey().register(new UserResourceList(userDao, jobTitleDAO, roleDao));
    environment.jersey().register(new ProgramResource(programDao));
    environment.jersey().register(new ProgramResourceList(programDao));
    environment.jersey().register(new OfferingResource(offeringDao, programDao));
    environment.jersey().register(new OfferingResourceList(offeringDao,programDao));
    environment.jersey().register(new OutcomeResource(outcomeDao, courseDao));
    environment.jersey().register(new OutcomeResourceList(outcomeDao, programDao, courseDao));
    environment.jersey().register(new AssignResource(assignDao, courseDao));
    environment.jersey().register(new AssignResourceList(assignDao, courseDao));
	  environment.jersey().register(new MetricResource(metricDao, programDao));
    environment.jersey().register(new MetricResourceList(metricDao));
	  environment.jersey().register(new SemesterResource(semesterDao));
    environment.jersey().register(new JobTitleResource(jobTitleDAO));
    environment.jersey().register(new JobTitleResourceList(jobTitleDAO));
    environment.jersey().register(new SemesterResourceList(semesterDao));
    environment.jersey().register(new ScaleResource(scaleDao));
    environment.jersey().register(new ScaleResourceList(scaleDao, programDao));
	  environment.jersey().register(new CourseResource(courseDao));
	  environment.jersey().register(new CourseResourceList( courseDao));
	  environment.jersey().register(new CoursePrefixResource(courseprefixDAO, courseDao));
    environment.jersey().register(new CoursePrefixResourceList(courseprefixDAO, programDao, courseDao));
    environment.jersey().register(new PermissionsResource(permissionsDAO));
    environment.jersey().register(new PermissionsResourceList(permissionsDAO));
    environment.jersey().register(new PerformanceResource(performanceDAO, programDao));
    environment.jersey().register(new PerformanceResourceList(performanceDAO, programDao));
    environment.jersey().register(new StudentAssignResource(studentAssignDAO, programDao));
    environment.jersey().register(new StudentAssignResourceList(studentAssignDAO, programDao));
    environment.jersey().register(new CourseOutcomeResource(courseOutcomeDAO, courseDao));
    environment.jersey().register(new CourseOutcomeResourceList(courseOutcomeDAO, courseDao));
    environment.jersey().register(new OfferingOutcomeResource(offeringOutcomeDAO, programDao));
    environment.jersey().register(new OfferingOutcomeResourceList(offeringOutcomeDAO, programDao));
    environment.jersey().register(new SemesterTypeResource(semesterTypeDAO));
    environment.jersey().register(new SemesterTypeResourceList(semesterTypeDAO));
    environment.jersey().register(new ProgramCutoffResource(programCutoffDAO, programDao));
    environment.jersey().register(new ProgramCutoffResourceList(programCutoffDAO));
    environment.jersey().register(new StudentOutcomeResourceList(studentOutcomeDAO, programDao));
    environment.jersey().register(new StudentOutcomeResource(studentOutcomeDAO, programDao));
    environment.jersey().register(new OutcomeAssignResource(outcomeAssignDAO, courseDao));
    environment.jersey().register(new OutcomeAssignResourceList(outcomeAssignDAO, courseDao));
    environment.jersey().register(new RoleResource(roleDao));
    environment.jersey().register(new RoleResourceList(roleDao));
    environment.jersey().register(new OfferingStudentResource(offeringStudentDao, programDao));
    environment.jersey().register(new OfferingStudentResourceList(offeringStudentDao, programDao));

    //Query By Selector instantiation and input of static variables to keep do required queries
    QueryBySelector queryBySelector = new QueryBySelector();
    queryBySelector.setDAOs(programDao,permissionsDAO,userDao);

  }
}
