namespace ScrumPinboard.Models.Parameters
{
    public class ProjectDeveloperRemoveData
    {
        public int ProjectId { get; set; }
        public int? DeveloperId { get; set; }

        public ProjectDeveloperRemoveData(int projectId, int? developerId)
        {
            ProjectId = projectId;
            DeveloperId = developerId;
        }
    }
}
