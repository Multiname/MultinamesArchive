using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using Microsoft.IdentityModel.Tokens;
using ScrumPinboard.Models;
using ScrumPinboard.Models.Parameters;
using System.IdentityModel.Tokens.Jwt;
using System.Security.Claims;
using System.Security.Cryptography;

namespace ScrumPinboard.Controllers
{
    [ApiController]
    [Route("[controller]")]
    public class MainController : ControllerBase
    {
        private static List<Dictionary<string, int>> projectsChanges = new();
        private static Dictionary<int, int> membershipChanges = new();

        private readonly ILogger<MainController> _logger;

        public MainController(ILogger<MainController> logger)
        {
            _logger = logger;
        }

        private string GenerateTag()
        {
            string tag;
            using ApplicationContext db = new();
            Developer? developer;

            do
            {
                tag = "";

                for (int i = 0; i < 3; ++i)
                {
                    int code = RandomNumberGenerator.GetInt32(36);
                    if (code < 10)
                        tag += (char)(code + 48);
                    else
                        tag += (char)(code + 55);
                }

                developer = db.Developers.FirstOrDefault(x => x.Tag == tag);
            } while (developer != null);

            return tag;
        }

        private void UpdateProjectChanges(int projectId, string key)
        {
            int index = projectsChanges.FindIndex(x => x["id"] == projectId);
            if (index == -1)
                return;

            ++projectsChanges[index][key];
        }

        private void UpdateMembershipChanges(int developerId)
        {
            if (membershipChanges.ContainsKey(developerId))
                ++membershipChanges[developerId];
        }

        [HttpGet("/GetProjectChanges")]
        [Authorize]
        public ActionResult GetProjectChanges(int projectId)
        {
            var identity = HttpContext.User.Identity as ClaimsIdentity;
            if (identity == null)
                return Unauthorized();

            string login = identity.FindFirst("login").Value;

            using ApplicationContext db = new();
            Developer? developer = db.Developers.FirstOrDefault(x => x.Login == login);

            if (developer == null)
                return NotFound();

            Dictionary<string, int>? projectChanges = projectsChanges.FirstOrDefault(x => x["id"] == projectId);
            if (projectChanges == null)
            {
                projectChanges = new()
                {
                    { "id", projectId },
                    { "name", 0 },
                    { "members", 0 },
                    { "sprints", 0 },
                    { "boards", 0 },
                    { "backlog", 0 }
                };
                projectsChanges.Add(projectChanges);
            }

            return new ObjectResult(projectChanges);
        }

        [HttpGet("/GetMembershipChanges")]
        [Authorize]
        public ActionResult GetMembershipChanges()
        {
            var identity = HttpContext.User.Identity as ClaimsIdentity;
            if (identity == null)
                return Unauthorized();

            string login = identity.FindFirst("login").Value;

            using ApplicationContext db = new();
            Developer? developer = db.Developers.FirstOrDefault(x => x.Login == login);

            if (developer == null)
                return NotFound();

            if (!membershipChanges.ContainsKey(developer.Id))
                membershipChanges.Add(developer.Id, 0);
            return new ObjectResult(membershipChanges[developer.Id]);
        }





        [HttpPost("/Login")]
        public ActionResult Login([FromBody] LoginData data)
        {
            using ApplicationContext db = new();
            Developer? developer = db.Developers.FirstOrDefault(x => x.Login == data.Login && x.Password == data.Password);

            if (developer == null)
                return NotFound();

            var claims = new List<Claim> { new Claim("login", developer.Login) };
            var jwt = new JwtSecurityToken(
                issuer: AuthOptions.ISSUER,
                audience: AuthOptions.AUDIENCE,
                claims: claims,
                signingCredentials: new SigningCredentials(AuthOptions.GetSymmetricSecurityKey(), SecurityAlgorithms.HmacSha256)
            );

            return new ObjectResult(new {
                login = developer.Login,
                name = developer.Name,
                tag = developer.Tag,
                token = new JwtSecurityTokenHandler().WriteToken(jwt)
            });
        }

        [HttpPost("/Signup")]
        public ActionResult Signup([FromBody] SignupData data)
        {
            using ApplicationContext db = new();
            Developer? developer = db.Developers.FirstOrDefault(x => x.Login == data.Login);
            if (developer != null)
                return BadRequest();

            db.Developers.Add(new Developer
            {
                Login = data.Login,
                Password = data.Password,
                Name = data.Name,
                Tag = GenerateTag()
            });
            db.SaveChanges();

            return Ok();
        }

        [HttpPut("/EditDeveloperName")]
        [Authorize]
        public ActionResult EditDeveloperName([FromBody] NameEditData data)
        {
            var identity = HttpContext.User.Identity as ClaimsIdentity;
            if (identity == null)
                return Unauthorized();

            string login = identity.FindFirst("login").Value;

            using ApplicationContext db = new();
            Developer? developer = db.Developers.FirstOrDefault(x => x.Login == login);

            if (developer == null)
                return NotFound();

            developer.Name = data.Name;
            db.Developers.Update(developer);
            db.SaveChanges();
            return Ok();
        }

        [HttpPut("/EditDeveloperPassword")]
        [Authorize]
        public ActionResult EditDeveloperPassword([FromBody] PasswordEditData data)
        {
            var identity = HttpContext.User.Identity as ClaimsIdentity;
            if (identity == null)
                return Unauthorized();

            string login = identity.FindFirst("login").Value;

            using ApplicationContext db = new();
            Developer? developer = db.Developers.FirstOrDefault(x => x.Login == login);

            if (developer == null)
                return NotFound();

            if (developer.Password != data.OldPassword)
                return Forbid();

            developer.Password = data.NewPassword;
            db.Developers.Update(developer);
            db.SaveChanges();
            return Ok();
        }





        [HttpGet("/GetProjectDevelopers")]
        [Authorize]
        public ActionResult GetProjectDevelopers(int projectId)
        {
            var identity = HttpContext.User.Identity as ClaimsIdentity;
            if (identity == null)
                return Unauthorized();

            string login = identity.FindFirst("login").Value;

            using ApplicationContext db = new();
            Developer? developer = db.Developers.FirstOrDefault(x => x.Login == login);

            if (developer == null)
                return NotFound();

            Project? project = db.Projects.Include(x => x.DevelopersProjects).FirstOrDefault(x => x.Id == projectId);
            if (project == null)
                return NotFound();

            List<object> developers = new();
            bool isMember = false;
            foreach (DeveloperProject dp in project.DevelopersProjects)
            {
                string memberName = db.Developers.FirstOrDefault(x => x.Id == dp.DeveloperId).Name;
                if (dp.DeveloperId == developer.Id)
                    isMember = true;

                developers.Add(new
                {
                    id = dp.DeveloperId,
                    name = memberName,
                    isOwner = dp.IsOwner
                });
            }

            object response = new
            {
                isMember = isMember,
                developers = developers
            };

            return new ObjectResult(response);
        }

        [HttpPost("/AddProjectDeveloper")]
        [Authorize]
        public ActionResult AddProjectDeveloper([FromBody] ProjectDeveloperAddData data)
        {
            var identity = HttpContext.User.Identity as ClaimsIdentity;
            if (identity == null)
                return Unauthorized();

            string login = identity.FindFirst("login").Value;

            using ApplicationContext db = new();
            Developer? developer = db.Developers.FirstOrDefault(x => x.Login == login);

            if (developer == null)
                return NotFound();

            Developer? member = db.Developers.FirstOrDefault(x => x.Tag == data.Tag);
            if (member == null)
                return NotFound();

            DeveloperProject? dp = db.DevelopersProjects.FirstOrDefault(x => x.ProjectId == data.ProjectId && x.DeveloperId == member.Id);
            if (dp != null)
                return BadRequest();

            DeveloperProject developerProject = new()
            {
                ProjectId = data.ProjectId,
                DeveloperId = member.Id,
                IsOwner = false
            };

            db.DevelopersProjects.Add(developerProject);
            db.SaveChanges();

            UpdateProjectChanges(data.ProjectId, "members");
            UpdateMembershipChanges(member.Id);

            return Ok();
        }

        [HttpPost("/RemoveProjectDeveloper")]
        [Authorize]
        public ActionResult RemoveProjectDeveloper([FromBody] ProjectDeveloperRemoveData data)
        {
            var identity = HttpContext.User.Identity as ClaimsIdentity;
            if (identity == null)
                return Unauthorized();

            string login = identity.FindFirst("login").Value;

            using ApplicationContext db = new();
            Developer? developer = db.Developers.FirstOrDefault(x => x.Login == login);

            if (developer == null)
                return NotFound();

            if (data.DeveloperId == null)
                data.DeveloperId = developer.Id;

            DeveloperProject? dp = db.DevelopersProjects.FirstOrDefault(x => x.DeveloperId == data.DeveloperId && x.ProjectId == data.ProjectId);
            if (dp == null)
                return NotFound();

            db.Entry(dp).State = EntityState.Deleted;
            db.SaveChanges();

            UpdateProjectChanges(data.ProjectId, "members");
            UpdateMembershipChanges(data.DeveloperId.Value);

            return Ok();
        }





        [HttpPost("/AddProject")]
        [Authorize]
        public ActionResult AddProject([FromBody] ProjectAddData data)
        {
            var identity = HttpContext.User.Identity as ClaimsIdentity;
            if (identity == null)
                return Unauthorized();

            string login = identity.FindFirst("login").Value;

            using ApplicationContext db = new();
            Developer? developer = db.Developers.FirstOrDefault(x => x.Login == login);

            if (developer == null)
                return NotFound();

            Project project = new Project { Name = data.Name };
            project.DevelopersProjects.Add(new DeveloperProject
            {
                Developer = developer,
                IsOwner = true
            });

            db.Projects.Add(project);
            db.SaveChanges();

            return new ObjectResult(new
            {
                projectName = project.Name
            });
        }

        [HttpPut("/EditProjectName")]
        [Authorize]
        public ActionResult EditProjectName([FromBody] ProjectNameEditData data)
        {
            var identity = HttpContext.User.Identity as ClaimsIdentity;
            if (identity == null)
                return Unauthorized();

            string login = identity.FindFirst("login").Value;

            using ApplicationContext db = new();
            Developer? developer = db.Developers.FirstOrDefault(x => x.Login == login);

            if (developer == null)
                return NotFound();

            Project? project = db.Projects.Include(x => x.Developers).FirstOrDefault(x => x.Id == data.ProjectId);
            if (project == null)
                return NotFound();

            project.Name = data.Name;
            db.Projects.Update(project);
            db.SaveChanges();

            UpdateProjectChanges(data.ProjectId, "name");
            foreach (Developer dev in project.Developers)
                UpdateMembershipChanges(dev.Id);

            return Ok();
        }

        [HttpGet("/GetProjects")]
        [Authorize]
        public ActionResult GetProjects()
        {
            var identity = HttpContext.User.Identity as ClaimsIdentity;
            if (identity == null)
                return Unauthorized();

            string login = identity.FindFirst("login").Value;

            using ApplicationContext db = new();
            Developer? developer = db.Developers.Include(x => x.Projects).FirstOrDefault(x => x.Login == login);

            if (developer == null)
                return NotFound();

            List<object> response = new();
            foreach (Project project in developer.Projects)
            {
                DeveloperProject? dp = db.DevelopersProjects.Include(x => x.Developer).FirstOrDefault(x => x.ProjectId == project.Id && x.IsOwner == true);
                string ownerName = dp.Developer.Name;
                response.Add(new
                {
                    id = project.Id,
                    name = project.Name,
                    owner = ownerName,
                    isOwner = developer.Id == dp.DeveloperId
                });
            }

            return new ObjectResult(response);
        }

        [HttpGet("/GetProject")]
        [Authorize]
        public ActionResult GetProject(int projectId)
        {
            var identity = HttpContext.User.Identity as ClaimsIdentity;
            if (identity == null)
                return Unauthorized();

            string login = identity.FindFirst("login").Value;

            using ApplicationContext db = new();
            Developer? developer = db.Developers.Include(x => x.Projects).FirstOrDefault(x => x.Login == login);

            if (developer == null)
                return NotFound();

            Project? project = db.Projects.FirstOrDefault(x => x.Id == projectId);
            if (project == null)
                return NotFound();

            return new ObjectResult(new
            {
                projectName = project.Name
            });
        }

        [HttpPost("/RemoveProject")]
        [Authorize]
        public ActionResult RemoveProject([FromBody] ProjectRemoveData data)
        {
            var identity = HttpContext.User.Identity as ClaimsIdentity;
            if (identity == null)
                return Unauthorized();

            string login = identity.FindFirst("login").Value;

            using ApplicationContext db = new();
            Developer? developer = db.Developers.FirstOrDefault(x => x.Login == login);

            if (developer == null)
                return NotFound();

            Project? project = db.Projects.Include(x => x.Developers).FirstOrDefault(x => x.Id == data.ProjectId);
            if (project == null)
                return NotFound();

            foreach (Developer dev in project.Developers)
                UpdateMembershipChanges(dev.Id);

            db.Entry(project).State = EntityState.Deleted;
            db.SaveChanges();
            return Ok();
        }





        [HttpPost("/AddEpic")]
        [Authorize]
        public ActionResult AddEpic([FromBody] EpicAddData data)
        {
            var identity = HttpContext.User.Identity as ClaimsIdentity;
            if (identity == null)
                return Unauthorized();

            string login = identity.FindFirst("login").Value;

            using ApplicationContext db = new();
            Developer? developer = db.Developers.FirstOrDefault(x => x.Login == login);

            if (developer == null)
                return NotFound();

            Project? project = db.Projects.FirstOrDefault(x => x.Id == data.ProjectId);
            if (project == null)
                return NotFound();

            Epic epic = new()
            {
                Name = data.Name,
                EpicPriority = data.Priority,
                IsDone = false
            };

            project.Epics.Add(epic);

            db.Projects.Update(project);
            db.SaveChanges();

            UpdateProjectChanges(data.ProjectId, "backlog");

            return Ok();
        }

        [HttpGet("/GetEpics")]
        [Authorize]
        public ActionResult GetEpics(int projectId)
        {
            var identity = HttpContext.User.Identity as ClaimsIdentity;
            if (identity == null)
                return Unauthorized();

            string login = identity.FindFirst("login").Value;

            using ApplicationContext db = new();
            Developer? developer = db.Developers.FirstOrDefault(x => x.Login == login);

            if (developer == null)
                return NotFound();

            Project? project = db.Projects.Include(x => x.Epics).FirstOrDefault(x => x.Id == projectId);
            if (project == null)
                return NotFound();

            List<object> response = new();
            foreach (Epic epic in project.Epics)
            {
                response.Add(new
                {
                    id = epic.Id,
                    name = epic.Name,
                    priority = epic.EpicPriority,
                    isDone = epic.IsDone
                });
            }

            return new ObjectResult(response);
        }

        [HttpPut("/EditEpicName")]
        [Authorize]
        public ActionResult EditEpicName([FromBody] EpicNameEditData data)
        {
            var identity = HttpContext.User.Identity as ClaimsIdentity;
            if (identity == null)
                return Unauthorized();

            string login = identity.FindFirst("login").Value;

            using ApplicationContext db = new();
            Developer? developer = db.Developers.FirstOrDefault(x => x.Login == login);

            if (developer == null)
                return NotFound();

            Epic? epic = db.Epics.FirstOrDefault(x => x.Id == data.EpicId);
            if (epic == null)
                return NotFound();

            epic.Name = data.Name;
            db.Epics.Update(epic);
            db.SaveChanges();

            UpdateProjectChanges(epic.ProjectId, "backlog");

            return Ok();
        }

        [HttpPut("/EditEpicPriority")]
        [Authorize]
        public ActionResult EditEpicPriority([FromBody] EpicPriorityEditData data)
        {
            var identity = HttpContext.User.Identity as ClaimsIdentity;
            if (identity == null)
                return Unauthorized();

            string login = identity.FindFirst("login").Value;

            using ApplicationContext db = new();
            Developer? developer = db.Developers.FirstOrDefault(x => x.Login == login);

            if (developer == null)
                return NotFound();

            Epic? epic = db.Epics.FirstOrDefault(x => x.Id == data.EpicId);
            if (epic == null)
                return NotFound();

            epic.EpicPriority = data.Priority;
            db.Epics.Update(epic);
            db.SaveChanges();

            UpdateProjectChanges(epic.ProjectId, "backlog");

            return Ok();
        }

        [HttpPut("/EditEpicIsDone")]
        [Authorize]
        public ActionResult EditEpicIsDone([FromBody] EpicIsDoneEditData data)
        {
            var identity = HttpContext.User.Identity as ClaimsIdentity;
            if (identity == null)
                return Unauthorized();

            string login = identity.FindFirst("login").Value;

            using ApplicationContext db = new();
            Developer? developer = db.Developers.FirstOrDefault(x => x.Login == login);

            if (developer == null)
                return NotFound();

            Epic? epic = db.Epics.FirstOrDefault(x => x.Id == data.EpicId);
            if (epic == null)
                return NotFound();

            epic.IsDone = data.IsDone;
            db.Epics.Update(epic);
            db.SaveChanges();

            UpdateProjectChanges(epic.ProjectId, "backlog");

            return Ok();
        }

        [HttpPost("/RemoveEpic")]
        [Authorize]
        public ActionResult RemoveEpic([FromBody] EpicRemoveData data)
        {
            var identity = HttpContext.User.Identity as ClaimsIdentity;
            if (identity == null)
                return Unauthorized();

            string login = identity.FindFirst("login").Value;

            using ApplicationContext db = new();
            Developer? developer = db.Developers.FirstOrDefault(x => x.Login == login);

            if (developer == null)
                return NotFound();

            Epic? epic = db.Epics.FirstOrDefault(x => x.Id == data.EpicId);
            if (epic == null)
                return NotFound();

            db.Entry(epic).State = EntityState.Deleted;
            db.SaveChanges();

            UpdateProjectChanges(epic.ProjectId, "backlog");

            return Ok();
        }





        [HttpPost("/AddStory")]
        [Authorize]
        public ActionResult AddStory([FromBody] StoryAddData data)
        {
            var identity = HttpContext.User.Identity as ClaimsIdentity;
            if (identity == null)
                return Unauthorized();

            string login = identity.FindFirst("login").Value;

            using ApplicationContext db = new();
            Developer? developer = db.Developers.FirstOrDefault(x => x.Login == login);

            if (developer == null)
                return NotFound();

            Epic? epic = db.Epics.FirstOrDefault(x => x.Id == data.EpicId);
            if (epic == null)
                return NotFound();

            Story story = new()
            {
                Name = data.Name,
                StoryPoints = data.StoryPoints
            };

            epic.Stories.Add(story);

            db.Epics.Update(epic);
            db.SaveChanges();

            UpdateProjectChanges(epic.ProjectId, "backlog");

            return Ok();
        }

        [HttpGet("/GetStories")]
        [Authorize]
        public ActionResult GetStories(int epicId)
        {
            var identity = HttpContext.User.Identity as ClaimsIdentity;
            if (identity == null)
                return Unauthorized();

            string login = identity.FindFirst("login").Value;

            using ApplicationContext db = new();
            Developer? developer = db.Developers.FirstOrDefault(x => x.Login == login);

            if (developer == null)
                return NotFound();

            Epic? epic = db.Epics.Include(x => x.Stories).FirstOrDefault(x => x.Id == epicId);
            if (epic == null)
                return NotFound();

            List<object> response = new();
            foreach (Story story in epic.Stories)
            {
                response.Add(new
                {
                    id = story.Id,
                    name = story.Name,
                    developerId = story.DeveloperId,
                    storyPoints = story.StoryPoints
                });
            }

            return new ObjectResult(response);
        }

        [HttpPut("/EditStoryName")]
        [Authorize]
        public ActionResult EditStoryName([FromBody] StoryNameEditData data)
        {
            var identity = HttpContext.User.Identity as ClaimsIdentity;
            if (identity == null)
                return Unauthorized();

            string login = identity.FindFirst("login").Value;

            using ApplicationContext db = new();
            Developer? developer = db.Developers.FirstOrDefault(x => x.Login == login);

            if (developer == null)
                return NotFound();

            Story? story = db.Stories.Include(x => x.Epic).FirstOrDefault(x => x.Id == data.StoryId);
            if (story == null)
                return NotFound();

            story.Name = data.Name;
            db.Stories.Update(story);
            db.SaveChanges();

            UpdateProjectChanges(story.Epic.ProjectId, "backlog");
            UpdateProjectChanges(story.Epic.ProjectId, "boards");

            return Ok();
        }

        [HttpPut("/EditStoryPoints")]
        [Authorize]
        public ActionResult EditStoryPoints([FromBody] StoryPointsEditData data)
        {
            var identity = HttpContext.User.Identity as ClaimsIdentity;
            if (identity == null)
                return Unauthorized();

            string login = identity.FindFirst("login").Value;

            using ApplicationContext db = new();
            Developer? developer = db.Developers.FirstOrDefault(x => x.Login == login);

            if (developer == null)
                return NotFound();

            Story? story = db.Stories.Include(x => x.Epic).FirstOrDefault(x => x.Id == data.StoryId);
            if (story == null)
                return NotFound();

            story.StoryPoints = data.StoryPoints;
            db.Stories.Update(story);
            db.SaveChanges();

            UpdateProjectChanges(story.Epic.ProjectId, "backlog");

            return Ok();
        }

        [HttpPut("/EditStoryDeveloper")]
        [Authorize]
        public ActionResult EditStoryDeveloper([FromBody] StoryDeveloperEditData data)
        {
            var identity = HttpContext.User.Identity as ClaimsIdentity;
            if (identity == null)
                return Unauthorized();

            string login = identity.FindFirst("login").Value;

            using ApplicationContext db = new();
            Developer? developer = db.Developers.FirstOrDefault(x => x.Login == login);

            if (developer == null)
                return NotFound();

            Story? story = db.Stories.Include(x => x.Epic).FirstOrDefault(x => x.Id == data.StoryId);
            if (story == null)
                return NotFound();

            if (story.DeveloperId != null)
            {
                Developer? oldDeveloper = db.Developers.FirstOrDefault(x => x.Id == story.DeveloperId);
                oldDeveloper.Stories.Remove(story);
                db.Developers.Update(oldDeveloper);
            }

            if (data.DeveloperId != -1)
            {
                Developer? newDeveloper = db.Developers.FirstOrDefault(x => x.Id == data.DeveloperId);
                newDeveloper.Stories.Add(story);
                db.Developers.Update(newDeveloper);
            }

            db.SaveChanges();

            UpdateProjectChanges(story.Epic.ProjectId, "backlog");
            UpdateProjectChanges(story.Epic.ProjectId, "boards");

            return Ok();
        }

        [HttpPost("/RemoveStory")]
        [Authorize]
        public ActionResult RemoveStory([FromBody] StoryRemoveData data)
        {
            var identity = HttpContext.User.Identity as ClaimsIdentity;
            if (identity == null)
                return Unauthorized();

            string login = identity.FindFirst("login").Value;

            using ApplicationContext db = new();
            Developer? developer = db.Developers.FirstOrDefault(x => x.Login == login);

            if (developer == null)
                return NotFound();

            Story? story = db.Stories.Include(x => x.Epic).FirstOrDefault(x => x.Id == data.StoryId);
            if (story == null)
                return NotFound();

            db.Entry(story).State = EntityState.Deleted;
            db.SaveChanges();

            UpdateProjectChanges(story.Epic.ProjectId, "backlog");
            UpdateProjectChanges(story.Epic.ProjectId, "boards");

            return Ok();
        }





        [HttpPost("/RemoveTask")]
        [Authorize]
        public ActionResult RemoveTask([FromBody] TaskRemoveData data)
        {
            var identity = HttpContext.User.Identity as ClaimsIdentity;
            if (identity == null)
                return Unauthorized();

            string login = identity.FindFirst("login").Value;

            using ApplicationContext db = new();
            Developer? developer = db.Developers.FirstOrDefault(x => x.Login == login);

            if (developer == null)
                return NotFound();

            Models.Task? task = db.Tasks.Include(x => x.Story).ThenInclude(x => x.Epic).FirstOrDefault(x => x.Id == data.TaskId);
            if (task == null)
                return NotFound();

            db.Entry(task).State = EntityState.Deleted;
            db.SaveChanges();

            UpdateProjectChanges(task.Story.Epic.ProjectId, "backlog");

            return Ok();
        }

        [HttpPost("/AddTask")]
        [Authorize]
        public ActionResult AddTask([FromBody] TaskAddData data)
        {
            var identity = HttpContext.User.Identity as ClaimsIdentity;
            if (identity == null)
                return Unauthorized();

            string login = identity.FindFirst("login").Value;

            using ApplicationContext db = new();
            Developer? developer = db.Developers.FirstOrDefault(x => x.Login == login);

            if (developer == null)
                return NotFound();

            Story? story = db.Stories.Include(x => x.Epic).FirstOrDefault(x => x.Id == data.StoryId);
            if (story == null)
                return NotFound();

            Models.Task task = new()
            {
                Name = data.Name,
                EstimatedHours = data.EstimatedHours,
                IsDone = false
            };

            story.Tasks.Add(task);

            db.Stories.Update(story);
            db.SaveChanges();

            UpdateProjectChanges(story.Epic.ProjectId, "backlog");

            return Ok();
        }

        [HttpGet("/GetTasks")]
        [Authorize]
        public ActionResult GetTasks(int storyId)
        {
            var identity = HttpContext.User.Identity as ClaimsIdentity;
            if (identity == null)
                return Unauthorized();

            string login = identity.FindFirst("login").Value;

            using ApplicationContext db = new();
            Developer? developer = db.Developers.FirstOrDefault(x => x.Login == login);

            if (developer == null)
                return NotFound();

            Story? story = db.Stories.Include(x => x.Tasks).FirstOrDefault(x => x.Id == storyId);
            if (story == null)
                return NotFound();

            List<object> response = new();
            foreach (var task in story.Tasks)
            {
                response.Add(new
                {
                    id = task.Id,
                    name = task.Name,
                    estimatedHours = task.EstimatedHours,
                    isDone = task.IsDone
                });
            }

            return new ObjectResult(response);
        }

        [HttpPut("/EditTaskName")]
        [Authorize]
        public ActionResult EditTaskName([FromBody] TaskNameEditData data)
        {
            var identity = HttpContext.User.Identity as ClaimsIdentity;
            if (identity == null)
                return Unauthorized();

            string login = identity.FindFirst("login").Value;

            using ApplicationContext db = new();
            Developer? developer = db.Developers.FirstOrDefault(x => x.Login == login);

            if (developer == null)
                return NotFound();

            Models.Task? task = db.Tasks.Include(x => x.Story).ThenInclude(x => x.Epic).FirstOrDefault(x => x.Id == data.TaskId);
            if (task == null)
                return NotFound();

            task.Name = data.Name;
            db.Tasks.Update(task);
            db.SaveChanges();

            UpdateProjectChanges(task.Story.Epic.ProjectId, "backlog");

            return Ok();
        }

        [HttpPut("/EditTaskEstimatedHours")]
        [Authorize]
        public ActionResult EditTaskEstimatedHours([FromBody] TaskEstimatedHoursEditData data)
        {
            var identity = HttpContext.User.Identity as ClaimsIdentity;
            if (identity == null)
                return Unauthorized();

            string login = identity.FindFirst("login").Value;

            using ApplicationContext db = new();
            Developer? developer = db.Developers.FirstOrDefault(x => x.Login == login);

            if (developer == null)
                return NotFound();

            Models.Task? task = db.Tasks.Include(x => x.Story).ThenInclude(x => x.Epic).FirstOrDefault(x => x.Id == data.TaskId);
            if (task == null)
                return NotFound();

            task.EstimatedHours = data.EstimatedHours;
            db.Tasks.Update(task);
            db.SaveChanges();

            UpdateProjectChanges(task.Story.Epic.ProjectId, "backlog");

            return Ok();
        }

        [HttpPut("/EditTaskIsDone")]
        [Authorize]
        public ActionResult EditTaskIsDone([FromBody] TaskIsDoneEditData data)
        {
            var identity = HttpContext.User.Identity as ClaimsIdentity;
            if (identity == null)
                return Unauthorized();

            string login = identity.FindFirst("login").Value;

            using ApplicationContext db = new();
            Developer? developer = db.Developers.FirstOrDefault(x => x.Login == login);

            if (developer == null)
                return NotFound();

            Models.Task? task = db.Tasks.Include(x => x.Story).ThenInclude(x => x.Epic).FirstOrDefault(x => x.Id == data.TaskId);
            if (task == null)
                return NotFound();

            task.IsDone = data.IsDone;
            db.Tasks.Update(task);
            db.SaveChanges();

            UpdateProjectChanges(task.Story.Epic.ProjectId, "backlog");

            return Ok();
        }





        [HttpPost("/AddSprint")]
        [Authorize]
        public ActionResult AddSprint([FromBody] SprintAddData data)
        {
            var identity = HttpContext.User.Identity as ClaimsIdentity;
            if (identity == null)
                return Unauthorized();

            string login = identity.FindFirst("login").Value;

            using ApplicationContext db = new();
            Developer? developer = db.Developers.FirstOrDefault(x => x.Login == login);

            if (developer == null)
                return NotFound();

            Project? project = db.Projects.FirstOrDefault(x => x.Id == data.ProjectId);
            if (project == null)
                return NotFound();

            Sprint sprint = new Sprint
            {
                Name = data.Name,
                StartDate = DateTime.Parse(data.StartDate),
                EndDate = DateTime.Parse(data.EndDate)
            };

            project.Sprints.Add(sprint);

            db.Projects.Update(project);
            db.SaveChanges();

            UpdateProjectChanges(data.ProjectId, "sprints");

            return Ok();
        }

        [HttpGet("/GetSprints")]
        [Authorize]
        public ActionResult GetSprints(int projectId)
        {
            var identity = HttpContext.User.Identity as ClaimsIdentity;
            if (identity == null)
                return Unauthorized();

            string login = identity.FindFirst("login").Value;

            using ApplicationContext db = new();
            Developer? developer = db.Developers.FirstOrDefault(x => x.Login == login);

            if (developer == null)
                return NotFound();

            Project? project = db.Projects.Include(x => x.Sprints).FirstOrDefault(x => x.Id == projectId);
            if (project == null)
                return NotFound();

            List<object> response = new();
            foreach (var sprint in project.Sprints)
            {
                response.Add(new
                {
                    id = sprint.Id,
                    name = sprint.Name,
                    startDate = sprint.StartDate.ToString("dd.MM.yyyy"),
                    endDate = sprint.EndDate.ToString("dd.MM.yyyy")
                });
            }

            return new ObjectResult(response);
        }

        [HttpGet("/GetStoriesAndEpics")]
        [Authorize]
        public ActionResult GetStoriesAndEpics(int projectId, int sprintId)
        {
            var identity = HttpContext.User.Identity as ClaimsIdentity;
            if (identity == null)
                return Unauthorized();

            string login = identity.FindFirst("login").Value;

            using ApplicationContext db = new();
            Developer? developer = db.Developers.FirstOrDefault(x => x.Login == login);

            if (developer == null)
                return NotFound();

            Project? project = db.Projects.Include(x => x.Epics).ThenInclude(x => x.Stories).FirstOrDefault(x => x.Id == projectId);
            if (project == null)
                return NotFound();

            Sprint? sprint = db.Sprints.Include(x => x.Stories).FirstOrDefault(x => x.Id == sprintId);
            if (sprint == null)
                return NotFound();

            List<object> response = new();
            foreach (var epic in project.Epics)
            {
                List<object> stories = new();
                foreach (var story in epic.Stories)
                {
                    Story? sought = sprint.Stories.FirstOrDefault(x => x.Id == story.Id);
                    bool isPicked = sought != null;

                    stories.Add(new
                    {
                        id = story.Id,
                        name = story.Name,
                        storyPoints = story.StoryPoints,
                        isPicked = isPicked
                    });
                }

                response.Add(new
                {
                    id = epic.Id,
                    name = epic.Name,
                    priority = epic.EpicPriority,
                    isDone = epic.IsDone,
                    stories = stories
                });
            }

            return new ObjectResult(response);
        }

        [HttpPut("/EditStoryIsPicked")]
        [Authorize]
        public ActionResult EditStoryIsPicked([FromBody] StoryIsPickedEditData data)
        {
            var identity = HttpContext.User.Identity as ClaimsIdentity;
            if (identity == null)
                return Unauthorized();

            string login = identity.FindFirst("login").Value;

            using ApplicationContext db = new();
            Developer? developer = db.Developers.FirstOrDefault(x => x.Login == login);

            if (developer == null)
                return NotFound();

            Sprint? sprint = db.Sprints.Include(x => x.Stories).FirstOrDefault(x => x.Id == data.SprintId);
            if (sprint == null)
                return NotFound();

            Story? story = db.Stories.FirstOrDefault(x => x.Id == data.StoryId);
            if (story == null)
                return NotFound();

            if (data.IsPicked)
                sprint.Stories.Add(story);
            else
                sprint.Stories.Remove(story);

            db.Sprints.Update(sprint);
            db.SaveChanges();

            UpdateProjectChanges(sprint.ProjectId, "boards");

            return Ok();
        }

        [HttpPut("/EditSprintName")]
        [Authorize]
        public ActionResult EditSprintName([FromBody] SprintNameEditData data)
        {
            var identity = HttpContext.User.Identity as ClaimsIdentity;
            if (identity == null)
                return Unauthorized();

            string login = identity.FindFirst("login").Value;

            using ApplicationContext db = new();
            Developer? developer = db.Developers.FirstOrDefault(x => x.Login == login);

            if (developer == null)
                return NotFound();

            Sprint? sprint = db.Sprints.FirstOrDefault(x => x.Id == data.Id);
            if (sprint == null)
                return NotFound();

            sprint.Name = data.Name;
            db.Sprints.Update(sprint);
            db.SaveChanges();

            UpdateProjectChanges(sprint.ProjectId, "sprints");

            return Ok();
        }

        [HttpPut("/EditSprintDate")]
        [Authorize]
        public ActionResult EditSprintDate([FromBody] SprintDateEdit data)
        {
            var identity = HttpContext.User.Identity as ClaimsIdentity;
            if (identity == null)
                return Unauthorized();

            string login = identity.FindFirst("login").Value;

            using ApplicationContext db = new();
            Developer? developer = db.Developers.FirstOrDefault(x => x.Login == login);

            if (developer == null)
                return NotFound();

            Sprint? sprint = db.Sprints.FirstOrDefault(x => x.Id == data.Id);
            if (sprint == null)
                return NotFound();

            if (data.isStart)
                sprint.StartDate = DateTime.Parse(data.Date);
            else
                sprint.EndDate = DateTime.Parse(data.Date);

            db.Sprints.Update(sprint);
            db.SaveChanges();

            UpdateProjectChanges(sprint.ProjectId, "sprints");

            return Ok();
        }

        [HttpPost("/RemoveSprint")]
        [Authorize]
        public ActionResult RemoveSprint([FromBody] SprintRemoveData data)
        {
            var identity = HttpContext.User.Identity as ClaimsIdentity;
            if (identity == null)
                return Unauthorized();

            string login = identity.FindFirst("login").Value;

            using ApplicationContext db = new();
            Developer? developer = db.Developers.FirstOrDefault(x => x.Login == login);

            if (developer == null)
                return NotFound();

            Sprint? sprint = db.Sprints.FirstOrDefault(x => x.Id == data.sprintId);
            if (sprint == null)
                return NotFound();

            db.Entry(sprint).State = EntityState.Deleted;
            db.SaveChanges();

            UpdateProjectChanges(sprint.ProjectId, "sprints");

            return Ok();
        }





        [HttpGet("/GetSprintStories")]
        [Authorize]
        public ActionResult GetSprintStories(int sprintId)
        {
            var identity = HttpContext.User.Identity as ClaimsIdentity;
            if (identity == null)
                return Unauthorized();

            string login = identity.FindFirst("login").Value;

            using ApplicationContext db = new();
            Developer? developer = db.Developers.FirstOrDefault(x => x.Login == login);

            if (developer == null)
                return NotFound();

            Sprint? sprint = db.Sprints.Include(x => x.SprintsStories)
                                            .ThenInclude(x => x.Story)
                                                .ThenInclude(x => x.Epic)
                                        .Include(x => x.SprintsStories)
                                            .ThenInclude(x => x.Story)
                                                .ThenInclude(x => x.Developer)
                                        .FirstOrDefault(x => x.Id == sprintId);
            if (sprint == null)
                return NotFound();

            List<object> response = new();
            foreach (var ss in sprint.SprintsStories)
            {
                response.Add(new
                {
                    id = ss.StoryId,
                    name = ss.Story.Name,
                    state = ss.State,
                    epicName = ss.Story.Epic.Name,
                    storyPoints = ss.Story.StoryPoints,
                    developerName = ss.Story.Developer?.Name,
                    isAssigned = ss.Story.DeveloperId == developer.Id
                });
            }

            return new ObjectResult(response);
        }

        [HttpPut("/EditStoryState")]
        [Authorize]
        public ActionResult EditStoryState([FromBody] StoryStateEditData data)
        {
            var identity = HttpContext.User.Identity as ClaimsIdentity;
            if (identity == null)
                return Unauthorized();

            string login = identity.FindFirst("login").Value;

            using ApplicationContext db = new();
            Developer? developer = db.Developers.FirstOrDefault(x => x.Login == login);

            if (developer == null)
                return NotFound();

            SprintStory? sprintStory = db.SprintsStories.Include(x => x.Sprint).FirstOrDefault(x => x.StoryId == data.storyId);
            if (sprintStory == null)
                return NotFound();

            sprintStory.State = data.state;
            db.SprintsStories.Update(sprintStory);
            db.SaveChanges();

            UpdateProjectChanges(sprintStory.Sprint.ProjectId, "sprints");

            return Ok();
        }
    }
}