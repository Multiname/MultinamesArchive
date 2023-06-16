namespace ScrumPinboard.Models.Parameters
{
    public class SprintAddData
    {
        public string Name { get; set; }
        public int ProjectId { get; set; }
        public string StartDate { get; set; }
        public string EndDate { get; set; }

        public SprintAddData(string name, int projectId, string startDate, string endDate)
        {
            Name = name;
            ProjectId = projectId;
            StartDate = startDate;
            EndDate = endDate;
        }
    }
}
