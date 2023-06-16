namespace ScrumPinboard.Models.Parameters
{
    public class EpicIsDoneEditData
    {
        public int EpicId { get; set; }
        public bool IsDone { get; set; }

        public EpicIsDoneEditData(int epicId, bool isDone)
        {
            EpicId = epicId;
            IsDone = isDone;
        }
    }
}
