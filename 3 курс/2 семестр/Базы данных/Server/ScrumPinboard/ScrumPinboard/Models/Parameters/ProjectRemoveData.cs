namespace ScrumPinboard.Models.Parameters
{
    public class ProjectRemoveData
    {
        public int ProjectId { get; set; }

        public ProjectRemoveData(int projectId)
        {
            ProjectId = projectId;
        }
    }
}
