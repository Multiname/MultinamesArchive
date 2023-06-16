namespace ScrumPinboard.Models.Parameters
{
    public class EpicAddData
    {
        public string Name { get; set; }
        public int ProjectId { get; set; }
        public Epic.Priority Priority { get; set; }

        public EpicAddData(string name, int projectId, Epic.Priority priority)
        {
            Name = name;
            ProjectId = projectId;
            Priority = priority;
        }
    }
}
