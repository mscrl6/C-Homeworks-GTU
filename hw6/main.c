#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void file_operations() {

	FILE *product_ptr;
	FILE *stock_ptr;

	char type;
	char name[8];
	char brand[5];
	double price;

	int stock_pID;
	char branch[15];
	int current_stock;
	int cProduct;
	int cStock;

	while(1) {
		// listing the operations
		printf("\n-------FILE OPERATIONS-------\n");
		printf("1- Add a new product.\n");
		printf("2- Delete a product.\n");
		printf("3- Update a product.\n");
		printf("4- Add a new stock entry.\n");
		printf("5- Delete a stock entry.\n");
		printf("6- Update a stock entry.\n");
		printf("7- Back to the main menu.\n");
		int option;
		scanf("%d", &option);
		if (option == 7) {
			break;
		}
		switch (option) {
			/*--------------------------------------------------------------------------------------------------------------*/
			//Adding a new product
			case 1: {
				printf("Please enter the type, name, brand and price of the product.\n");
				printf("Type (D, F, C, O): ");
				scanf(" %c", &type);
				printf("Name: ");
				scanf("%s", name);
				printf("Brand: ");
				scanf("%s", brand);
				printf("Price: ");
				scanf("%lf", &price);

				//opening the file
				product_ptr = fopen("products.txt", "a+");
				int pID = 1;
				rewind(product_ptr);
				while ((cProduct = fgetc(product_ptr)) != EOF) {
					if (cProduct == '\n') {
						pID++;
					}
				}
				//printing the product inputs to file
				fprintf(product_ptr, "%d,%c,%s,%s,%.2lf\n", pID, type, name, brand, price);
				printf("\nYou added a new product!\n");
				fclose(product_ptr);
				break;
			}
			
			/*--------------------------------------------------------------------------------------------------------------*/
			//deleting a product
			case 2: {

				int deleted_pID;
				printf("Please enter the pID that you want to delete: ");
				scanf("%d", &deleted_pID);

				int line = 1;

				product_ptr = fopen("products.txt", "r");
				
				//opening a temp file
				FILE* temp_ptr;
				temp_ptr = fopen("temp.txt", "w");

				int pIDtemp;

				while (fscanf(product_ptr, "%d,%c,%[^,],%[^,],%lf\n", &pIDtemp, &type, name, brand, &price) == 5) {
					
					//if line equals to pID that user wants to delete the program will continue
					if (line == deleted_pID) {
						line++;
						continue;
					}
					else if (line > deleted_pID) {
						pIDtemp--; //the pIDs after the deleted_pID will decrease
					}
					//printing the all products except deleted one to the temp file
					fprintf(temp_ptr, "%d,%c,%s,%s,%.2lf\n", pIDtemp, type, name, brand, price);
					line++;
				}

				fclose(product_ptr);
				fclose(temp_ptr);

				product_ptr = fopen("products.txt", "w+");
				temp_ptr = fopen("temp.txt", "r");
				
				//copying temp file to product file
				while (fscanf(temp_ptr, "%d,%c,%[^,],%[^,],%lf\n", &pIDtemp, &type, name, brand, &price) == 5) {
					fprintf(product_ptr, "%d,%c,%s,%s,%.2lf\n", pIDtemp, type, name, brand, price);
				}
				printf("\n%d. pID deleted!\n",deleted_pID);
				fclose(product_ptr);
				fclose(temp_ptr);
				break;
			}

			/*--------------------------------------------------------------------------------------------------------------*/
			//updating a feature of a product
			case 3: {

				int updated_pID;
				int feature;

				printf("Which pID do you want to update?");
				scanf("%d", &updated_pID);
				printf("Which feature do you want to update? (pID can not be updated).\n");
				printf("1. Type\n2. Name\n3. Brand\n4. Price\n");
				printf("Please enter the feature: ");
				scanf(" %d", &feature);

				product_ptr = fopen("products.txt", "r");

				int line = 1;


				switch (feature){
					
					//updating the type
					case 1: {

						char updated_type;
						printf("What is the new type of the product?\nPlease enter: ");
						scanf(" %c", &updated_type);			
			
						rewind(product_ptr);

						FILE* tmp_file = fopen("temp.txt", "w");

						if (tmp_file == NULL) {
							printf("Error!\n");
						}

						int pID = 1;
						while (fscanf(product_ptr, "%d,%c,%[^,],%[^,],%lf\n", &pID, &type, name, brand, &price) == 5) {

							//if pID equals to the pID that user wants to update the program prints the updated type.
							if (pID == updated_pID) {
								fprintf(tmp_file, "%d,%c,%s,%s,%.2lf\n", updated_pID, updated_type, name, brand, price);
							}
							else {
								fprintf(tmp_file, "%d,%c,%s,%s,%.2lf\n", pID, type, name, brand, price);
							}
							pID++;
						}

						fclose(product_ptr);
						fclose(tmp_file);

						product_ptr = fopen("products.txt", "w+");
						tmp_file = fopen("temp.txt", "r");

						//copying temp file to product file
						while (fscanf(tmp_file, "%d,%c,%[^,],%[^,],%lf\n", &pID, &type, name, brand, &price) == 5) {
							fprintf(product_ptr, "%d,%c,%s,%s,%.2lf\n", pID, type, name, brand, price);
						}
						fclose(product_ptr);
						fclose(tmp_file);
						printf("Updating is done!\n");
						break;
					}
					
					//updating the name
					case 2: {

						char updated_name[8];

						printf("What is the new name of the product?\nPlease enter: ");
						scanf("%s", updated_name);

						rewind(product_ptr);
						
						FILE* tmp_file = fopen("temp", "w");
						if (tmp_file == NULL) {
							printf("Error!\n");
						}

						int pID = 1;
						while (fscanf(product_ptr, "%d,%c,%[^,],%[^,],%lf\n", &pID, &type, name, brand, &price)==5) {
							//if pID equals to the pID that user wants to update the program prints the updated type.
							if (pID == updated_pID) {
								fprintf(tmp_file, "%d,%c,%s,%s,%.2lf\n", updated_pID, type, updated_name, brand, price);
							}
							else {
								fprintf(tmp_file, "%d,%c,%s,%s,%.2lf\n", pID, type, name, brand, price);
							}
							pID++;
						}
						fclose(product_ptr);
						fclose(tmp_file);

						product_ptr = fopen("products.txt", "w+");
						tmp_file = fopen("temp", "r");

						//copying temp file to product file
						while (fscanf(tmp_file, "%d,%c,%[^,],%[^,],%lf\n", &pID, &type, name, brand, &price) == 5) {
							fprintf(product_ptr, "%d,%c,%s,%s,%.2lf\n", pID, type, name, brand, price);
						}
						fclose(product_ptr);
						fclose(tmp_file);
						printf("Updating is done!\n");
						break;
					}

					//updating the brand
					case 3: {
						char updated_brand[5];
						printf("What is the new brand of the product?\nPlease enter: ");
						scanf("%s", updated_brand);

						rewind(product_ptr);

						FILE* tmp_file = fopen("temp.txt", "w");
						if (tmp_file == NULL) {
							printf("Error!\n");
						}

						int pID = 1;

						while (fscanf(product_ptr, "%d,%c,%[^,],%[^,],%lf\n", &pID, &type, name, brand, &price)==5) {
							//if pID equals to the pID that user wants to update the program prints the updated type.
							if (pID == updated_pID) {
								fprintf(tmp_file, "%d,%c,%s,%s,%.2lf\n", updated_pID, type, name, updated_brand, price);
							}
							else {
								fprintf(tmp_file, "%d,%c,%s,%s,%.2lf\n", pID, type, name, brand, price);
							}
							pID++;
						}

						fclose(product_ptr);
						fclose(tmp_file);

						product_ptr = fopen("products.txt", "w+");
						tmp_file = fopen("temp.txt", "r");

						//copying temp file to product file
						while (fscanf(tmp_file, "%d,%c,%[^,],%[^,],%lf\n", &pID, &type, name, brand, &price) == 5) {
							fprintf(product_ptr, "%d,%c,%s,%s,%.2lf\n", pID, type, name, brand, price);
						}
						fclose(product_ptr);
						fclose(tmp_file);
						printf("Updating is done!\n");
						break;
					}

					//updating the price
					case 4: {
						double updated_price;
						printf("What is the new price of the product?\nPlease enter: ");
						scanf("%lf", &updated_price);

						rewind(product_ptr);

						FILE* tmp_file = fopen("temp.txt", "w");
						if (tmp_file == NULL) {
							printf("Error!\n");
						}

						int pID = 1;
						while (fscanf(product_ptr, "%d,%c,%[^,],%[^,],%lf\n", &pID, &type, name, brand, &price)==5) {
							//if pID equals to the pID that user wants to update the program prints the updated type.
							if (pID == updated_pID) {
								fprintf(tmp_file, "%d,%c,%s,%s,%.2lf\n", updated_pID, type, name, brand, updated_price);
							}
							else {
								fprintf(tmp_file, "%d,%c,%s,%s,%.2lf\n", pID, type, name, brand, price);
							}
							pID++;
						}

						fclose(product_ptr);
						fclose(tmp_file);

						product_ptr = fopen("products.txt", "w+");
						tmp_file = fopen("temp.txt", "r");

						//copying temp file to product file
						while (fscanf(tmp_file, "%d,%c,%[^,],%[^,],%lf\n", &pID, &type, name, brand, &price) == 5) {
							fprintf(product_ptr, "%d,%c,%s,%s,%.2lf\n", pID, type, name, brand, price);
						}
						fclose(product_ptr);
						fclose(tmp_file);
						printf("Updating is done!\n");
						break;

					}

					default: {
						printf("Invalid input. Please enter a number between 1-4\n");
						fclose(product_ptr);
						break;
					}
				}

			}

			//Adding a new stock entry
			case 4: {

				stock_ptr = fopen("stocks.txt", "a+");
				printf("Please enter the pID, branch and current stock of the product.\n");
				printf("pID: ");
				scanf("%d", &stock_pID);
				printf("Branch name: ");
				scanf("%s", branch);
				printf("Stock: ");
				scanf("%d", &current_stock);


				int sID=1;

				rewind(stock_ptr);

				//Finding the number of line. 
				while ((cStock = fgetc(stock_ptr)) != EOF) {
					if (cStock == '\n') {
						sID++;
					}
				}

				//printing the stock inputs to file
				fprintf(stock_ptr, "%d,%d,%s,%d\n", sID, stock_pID, branch, current_stock);
				printf("\nNew stock entry is done!\n");
				fclose(stock_ptr);

				break;
			}

			/*--------------------------------------------------------------------------------------------------------------*/
			//deleting a stock entry
			case 5: {

				int deleted_sID;
				printf("Please enter the sID that you want to delete: ");
				scanf("%d", &deleted_sID);

				int line = 1;

				stock_ptr = fopen("stocks.txt", "r");

				FILE* S_temp_ptr;
				S_temp_ptr = fopen("temp.txt", "w");

				int sIDtemp;

				while (fscanf(stock_ptr, "%d,%d,%[^,],%d\n", &sIDtemp,&stock_pID, branch, &current_stock) == 4) {
					
					//if line equals to sID that user wants to delete the program will continue
					if (line == deleted_sID) {
						line++;
						continue;
					}
					else if (line > deleted_sID) {
						sIDtemp--;//the sIDs after the deleted_sID will decrease
					}
					fprintf(S_temp_ptr, "%d,%d,%s,%d\n", sIDtemp, stock_pID, branch, current_stock);
					line++;
				}

				fclose(stock_ptr);
				fclose(S_temp_ptr);

				stock_ptr = fopen("stocks.txt", "w");
				S_temp_ptr = fopen("temp.txt", "r");

				//After deleting the stock entry copying the products from temp file to stock file.
				while (fscanf(S_temp_ptr, "%d,%d,%[^,],%d\n", &sIDtemp, &stock_pID, branch, &current_stock) == 4) {
					fprintf(stock_ptr, "%d,%d,%s,%d\n", sIDtemp, stock_pID, branch, current_stock);
				}

				printf("\n%d. sID deleted!\n", deleted_sID);
				fclose(stock_ptr);
				fclose(S_temp_ptr);
				break;
			}

			/*--------------------------------------------------------------------------------------------------------------*/
			//updating a feature of a stock entry
			case 6: {

				int updated_sID;
				int feature;

				printf("Which sID do you want to update?\nPlease enter: ");
				scanf("%d", &updated_sID);
				printf("Which feature do you want to update? (sID and pID can not be updated).\n");
				printf("1. Branch\n2. Current Stock\n");
				printf("Please enter the feature: ");
				scanf("%d", &feature);

				stock_ptr = fopen("stocks.txt", "r");

				while (1) {
					if (feature == 1) {

						char updated_branch[15];
						printf("What is the new branch of the product?\nPlease enter: ");
						scanf("%s", updated_branch);

						rewind(stock_ptr);
						FILE* tmp_file = fopen("temp.txt", "w");

						int sID = 1;
						int pID;
						while (fscanf(stock_ptr, "%d,%d,%[^,],%d\n", &sID,&pID,branch,&current_stock) == 4) {

							//if sID equals to the pID that user wants to update the program prints the updated branch.
							if (sID == updated_sID) {
								fprintf(tmp_file, "%d,%d,%s,%d\n", updated_sID,pID,updated_branch,current_stock);
							}
							else {
								fprintf(tmp_file, "%d,%d,%s,%d\n", sID, pID, branch, current_stock);
							}
							sID++;
						}

						fclose(stock_ptr);
						fclose(tmp_file);

						stock_ptr = fopen("stocks.txt", "w+");
						tmp_file = fopen("temp.txt", "r");

						//copying temp file to stock file
						while (fscanf(tmp_file, "%d,%d,%[^,],%d\n", &sID, &pID, branch, &current_stock) == 4) {
							fprintf(stock_ptr, "%d,%d,%s,%d\n", sID, pID, branch, current_stock);
						}

						fclose(stock_ptr);
						fclose(tmp_file);

						printf("Updating is done!\n");
						break;

					}

					else if (feature == 2) {
						int updated_stock;
						printf("What is the new stock of the product?\nPlease enter: ");
						scanf("%d", &updated_stock);

						rewind(stock_ptr);
						FILE* tmp_file = fopen("temp.txt", "w");

						int sID = 1;
						int pID = 1;

						while (fscanf(stock_ptr, "%d,%d,%[^,],%d\n", &sID, &pID, branch, &current_stock) == 4) {
							//if sID equals to the pID that user wants to update the program prints the updated branch.
							if (sID == updated_sID) {
								fprintf(tmp_file, "%d,%d,%s,%d\n", updated_sID, pID, branch, updated_stock);
							}
							else {
								fprintf(tmp_file, "%d,%d,%s,%d\n", sID, pID, branch, current_stock);
							}
							sID++;
						}

						fclose(stock_ptr);
						fclose(tmp_file);

						stock_ptr = fopen("stocks.txt", "w+");
						tmp_file = fopen("temp.txt", "r");

						//copying temp file to stock file
						while (fscanf(tmp_file, "%d,%d,%[^,],%d\n", &sID, &pID, branch, &current_stock) == 4) {
							fprintf(stock_ptr, "%d,%d,%s,%d\n", sID, pID, branch, current_stock);
						}
						fclose(stock_ptr);
						fclose(tmp_file);

						printf("Updating is done!\n");
						break;
					}
					else {
						printf("Invalid input.\n");
					}
				}
			}
		}
	}
}
/************************************************END OF THE PART 1**********************************************************/

void query_products() {
	char type;
	char name[10];
	char brand[10];
	double price;
	int pID;

	FILE* product_ptr;
	product_ptr = fopen("products.txt", "r");

	while (1) {
		int option;

		printf("\n-------QUERY PRODUCTS-------\n");
		printf("1. List all products\n2. Filter products by brand, type, price, or a user-defined feature\n3. Back to main menu.\n");
		scanf("%d", &option);

		//listing all the products
		if (option == 1) {
			printf("All the products:\n");
			while (fscanf(product_ptr, "%d,%c,%[^,],%[^,],%lf\n", &pID, &type, name, brand, &price) == 5) {
				printf("%d,%c,%s,%s,%.2lf\n", pID, type, name,brand, price);
			}
			printf("\n");
			break;
		}

		//listing the products with given filters
		else if (option == 2) {
			char filter[50];
			printf("Enter the filters (type,brand,price_min,price_max): ");
			scanf("%s", filter);

			char* token = strtok(filter, ","); //getting the first filter
			char* filters[4] = { NULL }; // (brand, type, price_min, price_max)
			int i = 0;
			while (token != NULL && i < 6) {
				filters[i] = token; //in the for loop adding the filters to the filter array. 
				token = strtok(NULL, ",");
				i++;
			}

			//filtering the products

			fseek(product_ptr, 0, SEEK_SET);

			int num_filtered = 0;
			int j;
			while (fscanf(product_ptr, "%d,%c,%[^,],%[^,],%lf\n", &pID, &type, name, brand, &price) == 5) {
				int match = 1;
				for (j = 0; j < i && match; j += 2) {
					// check if the brand matches the filter 
					if (strcmp(filters[j], "brand") == 0 && strcmp(brand, filters[j + 1]) != 0) {
						match = 0; //whether the product matches the filters
					}
					// check if the type matches the filter 
					else if (strcmp(filters[j], "type") == 0 && type != filters[j + 1][0]) {
						match = 0;
					}
					// check if the price_min matches the filter 
					else if (strcmp(filters[j], "price_min") == 0 && price < atof(filters[j + 1])) {
						match = 0;
					}
					// check if the brand price_max the filter 
					else if (strcmp(filters[j], "price_max") == 0 && price > atof(filters[j + 1])) {
						match = 0;
					}
				}
				if (match) {
					//if match=1 printing the filtered products
					printf("%d,%c,%s,%s,%.2lf\n", pID, type, name, brand, price);
					num_filtered++;
				}
			}
			if (num_filtered == 0) {
				printf("No products match the filters.\n");
			}
			break;
		}
		else {
			printf("please enter a number between 1-3\n");
		}
	}
	printf("\n");
	fclose(product_ptr);
}

void check_stock_status() {

	while (1){
		int option;
		printf("1. Query the stock of a the product in a specified branch by using the product ID and branch name.\n");
		printf("2. List the stock of all products in a specified branch\n");
		printf("3. List the out-of-stock products in a specified branch\n");
		printf("4. Back to the menu.\n");
		scanf("%d", &option);

		struct stock_entry {
			int sID;
			int pID;
			char branch[20];
			int stock_count;
		};
		struct product_entry {
			int pID;
			char type;
			char name[20];
			char brand[20];
			float price;
		};

		if (option == 1) {
			struct stock_entry stock_entries[1000];
			struct product_entry product_entries[1000];
			int stock_count = 0;
			int product_count = 0;

			FILE* stock_ptr = fopen("stocks.txt", "r");
			if (stock_ptr == NULL) {
				printf("Error!\n");
				exit(1);
			}
			while (fscanf(stock_ptr, "%d,%d,%[^,],%d\n", &stock_entries[stock_count].sID, &stock_entries[stock_count].pID, stock_entries[stock_count].branch, &stock_entries[stock_count].stock_count) == 4) {
				stock_count++;
			}
			fclose(stock_ptr);

			FILE* product_ptr = fopen("products.txt", "r");
			if (product_ptr == NULL) {
				printf("Error!\n");
				exit(1);
			}

			//
			while (fscanf(product_ptr, "%d,%c,%[^,],%[^,],%f\n", &product_entries[product_count].pID, &product_entries[product_count].type, product_entries[product_count].name, product_entries[product_count].brand, &product_entries[product_count].price) == 5) {
				product_count++;
			}
			fclose(product_ptr);

			// Prompting the user to enter a branch name and a product ID
			char branch_name[20];
			int product_id;
			printf("Please enter the branch: ");
			scanf("%s", branch_name);
			printf("Please enter the product ID: ");
			scanf("%d", &product_id);

			struct stock_entry filtered_stock_entries[1000];

			// Filtering the stock entries array for the first entry with matching branch name and product ID
			int filtered_stock_count = 0;
			int i;
			for (i = 0; i < stock_count; i++) {
				if (stock_entries[i].pID == product_id && strcmp(stock_entries[i].branch, branch_name) == 0) {
					filtered_stock_entries[filtered_stock_count] = stock_entries[i];
					filtered_stock_count++;
				}
			}

			if (filtered_stock_count == 0) {
				printf("There is no stock entry related to given branch and pID.\n");
			}
			else {
				printf("Branch: %s Stock: %d \n", branch_name, filtered_stock_entries[0].stock_count);
			}
		}


		else if (option == 2) {
			// open stock file
			FILE* stock_ptr = fopen("stocks.txt", "r");
			if (stock_ptr == NULL) {
				printf("Stock file could not be opened.\n");
			}

			// read stock entries from file
			struct stock_entry stock_entries[1000];
			int num_stock_entries = 0;
			char line[100];
			while (fgets(line, sizeof(line), stock_ptr)) {
				sscanf(line, "%d,%d,%[^,],%d", &stock_entries[num_stock_entries].sID,
					&stock_entries[num_stock_entries].pID, stock_entries[num_stock_entries].branch,
					&stock_entries[num_stock_entries].stock_count);
				num_stock_entries++;
			}

			// close stock file
			fclose(stock_ptr);

			// open product file
			FILE* product_ptr = fopen("productS.txt", "r");
			if (product_ptr == NULL) {
				printf("Product file could not be opened.\n");
			}

			// read product entries from file
			struct product_entry product_entries[1000];
			int num_product_entries = 0;
			while (fgets(line, sizeof(line), product_ptr)) {
				sscanf(line, "%d,%c,%[^,],%[^,],%f", &product_entries[num_product_entries].pID,
					&product_entries[num_product_entries].type, product_entries[num_product_entries].name,
					product_entries[num_product_entries].brand, &product_entries[num_product_entries].price);
				num_product_entries++;
			}

			// close product file
			fclose(product_ptr);

			// get user input for branch name
			char branch_name[50];
			printf("Enter branch name: ");
			scanf("%s", branch_name);

			// filter stock entries for specified branch
			struct stock_entry filtered_stock_entries[1000];
			int num_filtered_stock_entries = 0;
			int i;
			for (i = 0; i < num_stock_entries; i++) {
				if (strcmp(stock_entries[i].branch, branch_name) == 0) {
					filtered_stock_entries[num_filtered_stock_entries] = stock_entries[i];
					num_filtered_stock_entries++;
				}
			}

			// list stock of all products in specified branch
			for (i = 0; i < num_filtered_stock_entries; i++) {
				printf("Product ID: %d, Product Name: %s, Brand: %s, Stock Count: %d\n",
					filtered_stock_entries[i].pID,
					product_entries[filtered_stock_entries[i].pID - 1].name,
					product_entries[filtered_stock_entries[i].pID - 1].name,
					filtered_stock_entries[i].stock_count);
			}

			if (num_filtered_stock_entries == 0) {
				printf("No stock entries found for specified branch.\n");
			}

		}

		else if (option == 3) {
			// open stock file
			FILE* stock_ptr = fopen("stocks.txt", "r");
			if (stock_ptr == NULL) {
				printf("Stock file could not be opened.\n");
			}

			// read stock entries from file
			struct stock_entry stock_entries[1000];
			int num_stock_entries = 0;
			char line[100];
			while (fgets(line, sizeof(line), stock_ptr)) {
				sscanf(line, "%d,%d,%[^,],%d", &stock_entries[num_stock_entries].sID,
					&stock_entries[num_stock_entries].pID, stock_entries[num_stock_entries].branch,
					&stock_entries[num_stock_entries].stock_count);
				num_stock_entries++;
			}

			// close stock file
			fclose(stock_ptr);

			// open product file
			FILE* product_ptr = fopen("products.txt", "r");
			if (product_ptr == NULL) {
				printf("Product file could not be opened.\n");
			}

			// read product entries from file
			struct product_entry product_entries[1000];
			int num_product_entries = 0;
			while (fgets(line, sizeof(line), product_ptr)) {
				sscanf(line, "%d,%c,%[^,],%[^,],%f", &product_entries[num_product_entries].pID,
					&product_entries[num_product_entries].type, product_entries[num_product_entries].name,
					product_entries[num_product_entries].brand, &product_entries[num_product_entries].price);
				num_product_entries++;
			}

			// close product file
			fclose(product_ptr);

			// get user input for branch name
			char branch_name[50];
			printf("Enter branch name: ");
			scanf("%s", branch_name);

			// filter stock entries for specified branch
			struct stock_entry filtered_stock_entries[1000];
			int num_filtered_stock_entries = 0;
			int i,j;
			for (i = 0; i < num_stock_entries; i++) {
				if (strcmp(stock_entries[i].branch, branch_name) == 0) {
					filtered_stock_entries[num_filtered_stock_entries] = stock_entries[i];
					num_filtered_stock_entries++;
				}
			}

			// list out-of-stock products in specified branch
			int out_of_stock = 1;
			for (i = 0; i < num_product_entries; i++) {
				out_of_stock = 1;
				for (j = 0; j < num_filtered_stock_entries; j++) {
					if (filtered_stock_entries[j].pID == product_entries[i].pID &&
						filtered_stock_entries[j].stock_count > 0) {
						out_of_stock = 0;
						break;
					}
				}
				if (out_of_stock == 1) {
					printf("Product Name: %s Brand: %s is out of stock.\n",
						product_entries[i].name,
						product_entries[i].brand);
				}
			}

			if (num_filtered_stock_entries == 0)
			{
				printf("All products are out of stock in %s.\n", branch_name);
			}
		}
		else if (option == 4) {
			break;
		}
		else {
			printf("Invalid input\n");
		}
	}
}
/*-----------------------------------------------------------------------------------*/
void stock_control_by_brand() {
	struct Product {
        int pID;
        char type;
        char name[20];
        char brand[20];
        double price;
    };

    struct Stock {
        int sID;
        int pID;
        char city[20];
        int quantity;
    };

    struct Product products[1000];
    struct Stock stock[1000];
    char brand[20];
    int brand_stock[1000][3]; // 2D array to store brand's products with their current stock
    int num_products = 0;
    int num_stock = 0;

	// Read products from file
	FILE* prod_file = fopen("products.txt", "r");
	if (prod_file == NULL) {
		printf("Error: Unable to open products file\n");
	}
	while (fscanf(prod_file, "%d,%c,%[^,],%[^,],%lf\n", &products[num_products].pID, &products[num_products].type, products[num_products].name, products[num_products].brand, &products[num_products].price) == 5) {
		num_products++;
	}
	fclose(prod_file);

	// Reading stock from file
	FILE* stock_file = fopen("stocks.txt", "r");
	if (stock_file == NULL) {
		printf("Error: Unable to open stock file\n");
	}
	while (fscanf(stock_file, "%d,%d,%[^,],%d\n", &stock[num_stock].sID, &stock[num_stock].pID, stock[num_stock].city, &stock[num_stock].quantity) == 4) {
		num_stock++;
	}
	fclose(stock_file);

	// Geting brand name from user
	printf("Enter brand name: ");
	scanf("%s", brand);

	// Find products of the given brand and their current stock
	int num_brand_products = 0;
	int i,j;
	for ( i = 0; i < num_products; i++) {
        if (strcmp(products[i].brand, brand) == 0) {
            int pID = products[i].pID;
            int stock_qty = 0;
            for ( j = 0; j < num_stock; j++) {
                if (stock[j].pID == pID) {
                    stock_qty += stock[j].quantity;
                }
            }
            brand_stock[num_brand_products][0] = pID;      // storing pID
            brand_stock[num_brand_products][1] = products[i].price * 100;  // storing price
            brand_stock[num_brand_products][2] = stock_qty; // storing stock
            num_brand_products++;
        }
    }

	// Print brand's products and their current stock
    printf("Product ID\tPrice\t\tStock\n");
    for (i = 0; i < num_brand_products; i++) {
        printf("%d\t\t%.2lf\t\t%d\n", brand_stock[i][0], brand_stock[i][1] / 100.0, brand_stock[i][2]);
    }

	/*-----------------------------------------------------------------------------*/

	/*stock report*/
	
		// Writing report to file
FILE* report_file = fopen("report.txt", "w");
if (report_file == NULL) {
    printf("Error: Unable to open report file\n");
    return;
}

for ( i = 0; i < num_brand_products; i++) {
    int pID = brand_stock[i][0];
    int qty_sum = 0;
    int qty_count = 0;
    int min_qty = 1000000; 
    int max_qty = -1; 

    for ( j = 0; j < num_products; j++) {
        if (stock[j].pID == pID) {
            int qty = stock[j].quantity;
            if (qty < min_qty) {
                min_qty = qty;
            }
            if (qty > max_qty) {
                max_qty = qty;
            }
            qty_sum += qty;
            qty_count++;
        }
    }

    int median_qty;
    if (qty_count > 0) {
        median_qty = qty_sum / qty_count;
    }
    else {
        median_qty = 0;
    }

    double unit_price;
    if (qty_count > 0) {
        unit_price = brand_stock[i][1] / qty_count; // calculating unit price
    }
    else {
        unit_price = 0;
    }

    fprintf(report_file, "%d,%d,%d,%d\n", pID, min_qty, max_qty, median_qty);
}

fclose(report_file);
}

int main(){	
	int option;
	do{
		printf("Welcome to operator, please select an option to continue:\n1- File Operations\n");
		printf("2- Query products\n3- Check stock status\n4- Stock control by brand\n5- Export report\n");
		scanf("%d", &option);
		if (option < 1 || option>5) {
			printf("Invalid input.\n\n");
		}
		else {
			switch (option)
			{
				case 1: {
					file_operations();
					break;
				}
				case 2: {
					query_products();
					break;
				}
				case 3: {
					check_stock_status();
					break;
				}
				case 4: {
					stock_control_by_brand();
					break;
				}
				default:
					break;
			}
		}
	} while (option != 5);
}


