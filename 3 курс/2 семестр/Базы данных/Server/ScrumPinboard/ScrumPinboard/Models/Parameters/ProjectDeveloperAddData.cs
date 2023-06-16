namespace ScrumPinboard.Models.Parameters
{
    public class ProjectDeveloperAddData
    {
        public string Tag { get; set; }
        public int ProjectId { get; set; }

        public ProjectDeveloperAddData(string tag, int projectId)
        {
            Tag = tag;
            ProjectId = projectId;
        }
    }
}
