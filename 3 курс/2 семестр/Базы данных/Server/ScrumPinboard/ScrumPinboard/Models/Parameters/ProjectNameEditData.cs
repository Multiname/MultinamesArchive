namespace ScrumPinboard.Models.Parameters
{
    public class ProjectNameEditData
    {
        public int ProjectId { get; set; }
        public string Name { get; set; }

        public ProjectNameEditData(int projectId, string name)
        {
            ProjectId = projectId;
            Name = name;
        }
    }
}
