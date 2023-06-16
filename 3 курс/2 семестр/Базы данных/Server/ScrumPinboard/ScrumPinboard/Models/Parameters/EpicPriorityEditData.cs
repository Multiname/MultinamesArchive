namespace ScrumPinboard.Models.Parameters
{
    public class EpicPriorityEditData
    {
        public int EpicId { get; set; }
        public Epic.Priority Priority { get; set; }

        public EpicPriorityEditData(int epicId, Epic.Priority priority)
        {
            EpicId = epicId;
            Priority = priority;
        }
    }
}
