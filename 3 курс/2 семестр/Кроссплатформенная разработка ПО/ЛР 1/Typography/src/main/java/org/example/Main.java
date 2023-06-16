package org.example;

import models.Client;
import models.Contract;
import models.Product;
import services.ClientService;
import services.ContractService;
import services.ProductService;

import java.sql.SQLException;
import java.util.Collections;
import java.util.Scanner;

public class Main {
    static ClientService clientService = new ClientService();
    static ProductService productService = new ProductService();
    static ContractService contractService = new ContractService();

    static long InputLong() {
        Scanner scanner = new Scanner(System.in);
        return scanner.nextLong();
    }

    static double InputDouble() {
        Scanner scanner = new Scanner(System.in);
        return scanner.nextDouble();
    }

    static int InputInt() {
        Scanner scanner = new Scanner(System.in);
        return scanner.nextInt();
    }

    static String InputString() {
        Scanner scanner = new Scanner(System.in);
        return scanner.nextLine();
    }

    static void ShowClients() {
        System.out.printf("%10s %40s %20s %20s",
                "ID |",
                "ФИО |",
                "Номер телефона |",
                "Персональная скидка");
        System.out.println();
        System.out.print(String.join("", Collections.nCopies(93, "-")));
        System.out.println();
        for (var client : clientService.FindAllClients()) {
            System.out.printf("%10s %40s %20s %20s",
                    client.GetId() + " |",
                    client.GetName()  + " |",
                    client.GetPhoneNumber()  + " |",
                    client.GetSale() + "%");
            System.out.println();
        }
    }

    static void ShowProducts() {
        System.out.printf("%10s %40s %20s",
                "ID |",
                "Наименование |",
                "Стоимость за единицу");
        System.out.println();
        System.out.print(String.join("", Collections.nCopies(72, "-")));
        System.out.println();
        for (var product : productService.FindAllProducts()) {
            System.out.printf("%10s %40s %20s",
                    product.GetId() + " |",
                    product.GetName()  + " |",
                    product.GetPrice() + "р");
            System.out.println();
        }
    }

    static void ShowContracts() {
        System.out.printf("%10s %15s %15s %10s %10s",
                "ID |",
                "ID клиента |",
                "ID продукции |",
                "Тираж |",
                "Стоимость");
        System.out.println();
        System.out.print(String.join("", Collections.nCopies(64, "-")));
        System.out.println();
        for (var contract : contractService.FindAllContracts()) {
            System.out.printf("%10s %15s %15s %10s %10s",
                    contract.GetId() + " |",
                    contract.GetClient().GetId()  + " |",
                    contract.GetProduct().GetId()  + " |",
                    contract.GetCount()  + " |",
                    contract.GetAmount() + "р");
            System.out.println();
        }
    }

    static Client ChooseClient()
    {
        ShowClients();
        System.out.print("ID: ");
        long id = InputLong();
        return clientService.FindClient(id);
    }

    static Product ChooseProduct()
    {
        ShowProducts();
        System.out.print("ID: ");
        long id = InputLong();
        return productService.FindProduct(id);
    }

    static Contract ChooseContract()
    {
        ShowContracts();
        System.out.print("ID: ");
        long id = InputLong();
        return contractService.FindContract(id);
    }

    static void AddClient() {
        System.out.print("ФИО: ");
        String name = InputString();
        System.out.print("Телефон: ");
        long phoneNumber = InputLong();
        System.out.print("Скидка: ");
        double sale = InputDouble();

        Client client = new Client(name, phoneNumber, sale);
        clientService.SaveClient(client);
    }

    static void AddProduct() {
        System.out.print("Название: ");
        String name = InputString();
        System.out.print("Цена: ");
        double price = InputDouble();

        Product product = new Product(name, price);
        productService.SaveProduct(product);
    }

    static void AddContract() {
        System.out.println("Клиент");
        Client client = ChooseClient();
        System.out.println("Продукция");
        Product product = ChooseProduct();
        System.out.print("Тираж: ");
        int count = InputInt();

        Contract contract = new Contract(client, product, count);
        contractService.SaveContract(contract);
    }

    static void EditClient() {
        Client client = ChooseClient();
        System.out.println();

        System.out.println("Выберите поле");
        System.out.println("1. ФИО");
        System.out.println("2. Телефон");
        System.out.println("3. Скидка");
        System.out.print(">>> ");
        int code = InputInt();
        System.out.println();

        System.out.print("Новое значение: ");
        switch (code) {
            case 1 -> client.SetName(InputString());
            case 2 -> client.SetPhoneNumber(InputLong());
            case 3 -> client.SetSale(InputDouble());
            default -> {
                return;
            }
        }

        clientService.UpdateClient(client);
    }

    static void EditProduct() {
        Product product = ChooseProduct();
        System.out.println();

        System.out.println("Выберите поле");
        System.out.println("1. Название");
        System.out.println("2. Цена");
        System.out.print(">>> ");
        int code = InputInt();
        System.out.println();

        System.out.print("Новое значение: ");
        switch (code) {
            case 1 -> product.SetName(InputString());
            case 2 -> product.SetPrice(InputDouble());
            default -> {
                return;
            }
        }

        productService.UpdateProduct(product);
    }

    static void EditContract() {
        Contract contract = ChooseContract();
        System.out.println();

        System.out.println("Выберите поле");
        System.out.println("1. Клиент");
        System.out.println("2. Продукция");
        System.out.println("3. Тираж");
        System.out.print(">>> ");
        int code = InputInt();
        System.out.println();

        System.out.print("Новое значение: ");
        if (code == 1 || code == 2) System.out.println();
        switch (code) {
            case 1 -> contract.SetClient(ChooseClient());
            case 2 -> contract.SetProduct(ChooseProduct());
            case 3 -> contract.SetCount(InputInt());
            default -> {
                return;
            }
        }

        contractService.UpdateContract(contract);
    }

    static void DeleteClient() {
        clientService.DeleteClient(ChooseClient());
    }

    static void DeleteProduct() {
        productService.DeleteProduct(ChooseProduct());
    }

    static void DeleteContract() {
        contractService.DeleteContract(ChooseContract());
    }

    static boolean ShowMenu() {
        System.out.println("1. Просмотреть");
        System.out.println("2. Добавить");
        System.out.println("3. Изменить");
        System.out.println("4. Удалить");
        System.out.println("0. Выход");
        System.out.print(">>> ");
        int action = InputInt();

        if (action == 0) return false;
        if (action < 0 || action > 4) {
            System.out.println("Ошибка ввода");
            return true;
        }

        System.out.println();
        System.out.println("1. Клиентов");
        System.out.println("2. Продукцию");
        System.out.println("3. Договоры");
        System.out.print(">>> ");
        int table = InputInt();

        if (table < 1 || table > 3) {
            System.out.println("Ошибка ввода");
            return true;
        }

        System.out.println();
        if (action == 1) {
            switch (table) {
                case 1 -> ShowClients();
                case 2 -> ShowProducts();
                case 3 -> ShowContracts();
            }
        } else if (action == 2) {
            switch (table) {
                case 1 -> AddClient();
                case 2 -> AddProduct();
                case 3 -> AddContract();
            }
        } else if (action == 3) {
            switch (table) {
                case 1 -> EditClient();
                case 2 -> EditProduct();
                case 3 -> EditContract();
            }
        } else if (action == 4) {
            switch (table) {
                case 1 -> DeleteClient();
                case 2 -> DeleteProduct();
                case 3 -> DeleteContract();
            }
        } else {
            System.out.println("Ошибка ввода");
        }
        System.out.println();

        return true;
    }

    public static void main(String[] args) throws SQLException {
        while (ShowMenu());
    }
}