namespace CodeContractsDemo
{
    using System;
    using System.Diagnostics.Contracts;

    public class Payment
    {
        public string Name { get; set; }

        public DateTime Date { get; set; }

        public double Amount { get; set; }
    }

    [ContractClass(typeof(PaymentContract))]
    public interface IPayment
    {
        double Value { get; set; }

        void Add(Payment payment);

        void Add2(Payment[] payments);
    }

    [ContractClassFor(typeof(IPayment))]
    public abstract class PaymentContract : IPayment
    {
        public abstract double Value { get; set; }

        public void Add(Payment payment)
        {
            Contract.Requires(payment != null, "Payment can't be null");
            Contract.Requires(!string.IsNullOrEmpty(payment.Name), "Payment name can't be blank");
            Contract.Requires(payment.Date <= DateTime.Now, "Date can't be future");
            Contract.Requires(payment.Amount > 0, "Payment amount can't be negative");
        }

        public void Add2(Payment[] payments)
        {
            Contract.Requires(
                (payments != null) &&
                Contract.ForAll(payments, payment => payment != null), "Payments can't be null");
        }
    }

    public class PaymentProcessor : IPayment
    {

        public double Value { get; set; }

        public void Add(Payment payment)
        {
            this.Value += payment.Amount;
            Console.WriteLine("Payment has been made");
        }

        public void Add2(Payment[] payments)
        {
            foreach (var payment in payments)
            {
                this.Value += payment.Amount;
            }
        }
    }

    class Program
    {
        static void Contract_ContractFailed(object sender, ContractFailedEventArgs e)
        {
            Console.WriteLine(e.Message);
            e.SetUnwind();
            e.SetHandled();
        }

        static void Main(string[] args)
        {
            Contract.ContractFailed += new EventHandler<ContractFailedEventArgs>(Contract_ContractFailed);

            var paymentProcessor = new PaymentProcessor();
            paymentProcessor.Value = 0;

            var payment1 = new Payment
            {
                Name = "qwe",
                Amount = 100,
                Date = new DateTime(2008, 5, 1, 8, 30, 52)
            };

            paymentProcessor.Add(payment1);

            paymentProcessor.Add(null);
        }
    }
}