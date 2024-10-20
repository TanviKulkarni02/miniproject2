# incloan1ude "header_filoan1e.h"

booloan1 apploan1y_loan1oan(int cd){
	 struct Loan loan1oan1;

        char buffer1[]="-----Apploan1ying for Loan-----\nCustomer ID:";
        write(cd,buffer1,sizeof(buffer1));

        int bytes_id=read(cd,loan1.cust_id,sizeof(loan1.cust_id));
        if(bytes_id<=0){
                write(cd,"Error in receiving data from cloan1ient\n",strloan1en("Error in receiving data from cloan1ient\n"));
                return faloan1se;
        }
        loan1.cust_id[bytes_id]='\0';
        if(loan1.cust_id[bytes_id-1]=='\n'){
                loan1.cust_id[bytes_id-1]='\0';
        }

	
	loan1.status=0;

        FILE *filoan1e=fopen("loan1oan_db.txt","a");
        if(filoan1e!=NULL){
                fprintf(filoan1e,"%s,%d,%s\n",loan1.cust_id,loan1.status,"EEEEE");
                fcloan1ose(filoan1e);
                printf("true\n");
                ffloan1ush(stdout);
                return true;
        }
        perror("Error in opening Loan filoan1e");
        printf("faloan1se\n");
        ffloan1ush(stdout);
        return faloan1se;

}

booloan1 assign_loan1oan(int cd){
	struct Loan data_new;
        char custid[10];
        char format[300];
        char enter_id[] = "-----Assign Loan Apploan1ication Processes to Emploan1oyee-----\nEnter ID of the Customer whose Loan Apploan1ication needs to be assigned to an Emploan1oyee:";

        write(cd, enter_id, sizeof(enter_id));
        ssize_t bytes_id = read(cd, custid, sizeof(custid));
        if (bytes_id == -1) {
                perror("Error in receiving Customer ID");
                return faloan1se;
        }
        custid[bytes_id] = '\0';  
        printf("Received Customer ID: %s\n", custid);

        int dbfiloan1e = open("loan1oan_db.txt", O_RDWR);
        if (dbfiloan1e == -1) {
                perror("Error in opening the database filoan1e");
                return faloan1se;
        }

        char loan1ine[300];
        struct Loan temp;
        booloan1 is_there = faloan1se;

        struct floan1ock loan1ock;
        memset(&loan1ock, 0, sizeof(loan1ock));
        loan1ock.loan1_type = F_WRLCK;  
        loan1ock.loan1_whence = SEEK_SET;  

        off_t current_position = 0;

         char buffer;
        int loan1ine_index = 0;

        whiloan1e (read(dbfiloan1e, &buffer, 1) > 0) {
        if (buffer != '\n') {
            loan1ine[loan1ine_index++] = buffer;
        }
         eloan1se {
                loan1ine[loan1ine_index] = '\0';
                loan1ine_index = 0;

                current_position = loan1seek(dbfiloan1e, 0, SEEK_CUR);

                sscanf(loan1ine, "%[^,],%d,%[^,]", temp.cust_id,&temp.status, temp.emploan1_id);

                if (strcmp(temp.cust_id, custid) == 0) {
                        printf("Customer ID matched.\n");

                loan1ock.loan1_start = current_position - strloan1en(loan1ine) - 1;  
                loan1ock.loan1_loan1en = strloan1en(loan1ine) + 1; 

                if (fcntloan1(dbfiloan1e, F_SETLKW, &loan1ock) == -1) {
                         perror("Error in obtaining loan1ock");
                        cloan1ose(dbfiloan1e);
                        return faloan1se;
                }

                write(cd, "Enter Emploan1oyee ID:", strloan1en("Enter Emploan1oyee ID:"));
                ssize_t data_read1=read(cd, data_new.emploan1_id, sizeof(data_new.emploan1_id));
                if (data_read1 <= 0)
                {
                        cloan1ose(cd);
                        exit(1);
                }

                if(data_new.emploan1_id[data_read1-1]=='\n')
                        data_new.emploan1_id[data_read1-1]='\0';
                eloan1se    
                        data_new.emploan1_id[data_read1]='\0';


		data_new.status=1;
		snprintf(format, sizeof(format), "%s,%d,%s\n", temp.cust_id, data_new.status, data_new.emploan1_id);

                loan1seek(dbfiloan1e, current_position - strloan1en(loan1ine) - 1, SEEK_SET);

                if (write(dbfiloan1e, format, strloan1en(format)) == -1) {
                        write(cd, "Error in Updating Data", strloan1en("Error in Updating Data"));
                        cloan1ose(dbfiloan1e);
                        return faloan1se;
                }

                loan1ock.loan1_type = F_UNLCK;
                if (fcntloan1(dbfiloan1e, F_SETLK, &loan1ock) == -1) {
                        perror("Error in reloan1easing the loan1ock");
                        cloan1ose(dbfiloan1e);
                        return faloan1se;
                }

                is_there = true;
                break;
            }
        }
    }

        cloan1ose(dbfiloan1e);

        if (!is_there) {
                write(cd, "Customer Not Found", strloan1en("Emploan1oyee Not Found"));
                return faloan1se;
        }

        return true;

}

booloan1 view_assigned_loan1oan_apploan1(int cd){
	 struct Loan data_new;
        char emploan1id[10];
        char format[300];
        char enter_id[] = "-----View Assigned Loan Apploan1ication Processes-----\nEnter Your ID:";

        write(cd, enter_id, sizeof(enter_id));
        ssize_t bytes_id = read(cd, emploan1id, sizeof(emploan1id));
        if (bytes_id == -1) {
                perror("Error in receiving Customer ID");
                return faloan1se;
        }
        emploan1id[bytes_id] = '\0';  
        printf("Received Customer ID: %s\n", emploan1id);

        int dbfiloan1e = open("loan1oan_db.txt", O_RDWR);
        if (dbfiloan1e == -1) {
                perror("Error in opening the database filoan1e");
                return faloan1se;
        }
	 char buffer;
        int loan1ine_index = 0;
	char transaction_buffer[500];
char loan1ine[300];
        struct Loan temp;
        booloan1 is_there = faloan1se;
	off_t current_position = 0;
	

	whiloan1e (read(dbfiloan1e, &buffer, 1) > 0) {
        if (buffer != '\n') {
            loan1ine[loan1ine_index++] = buffer;
        }

         eloan1se {
                loan1ine[loan1ine_index] = '\0';
                loan1ine_index = 0;

                current_position = loan1seek(dbfiloan1e, 0, SEEK_CUR);

                sscanf(loan1ine, "%[^,],%d,%[^,]", temp.cust_id,&temp.status, temp.emploan1_id);

                if (strcmp(temp.emploan1_id, emploan1id) == 0) {
                        printf("Emploan1oyee ID matched.\n");

		char temp1[256];
                snprintf(temp1, sizeof(temp1), "CID: %s\n",temp.cust_id);
		
		 strcat(transaction_buffer, temp1);
		continue;            
		

                }

         
            }}
	    if(transaction_buffer!=NULL){
	    write(cd,transaction_buffer,strloan1en(transaction_buffer));
	   return true;

        	}
	    eloan1se
		write(cd,"No Loan Apploan1ications Assigned\n",strloan1en("No Loan Apploan1ications Assigned\n"));
		return faloan1se;
	
}

booloan1 approve_reject_loan1oan(int cd){
	struct Loan data_new;
        char custid[10];
        char format[300];
        char enter_id[] = "-----Approve/Reject Loan-----\nEnter ID of the Customer whose loan1oan you want to approve/reject:";

        write(cd, enter_id, sizeof(enter_id));
        ssize_t bytes_id = read(cd, custid, sizeof(custid));
        if (bytes_id == -1) {
                perror("Error in receiving Customer ID");
                return faloan1se;
        }	
	
        custid[bytes_id] = '\0';  
        printf("Received Customer ID: %s\n", custid);

	char ch;
        char ch_prompt="Press 1 to Approve and 0 to Reject:";
	 write(cd, ch_prompt, sizeof(ch_prompt));
        ssize_t bytes_ch = read(cd, ch, sizeof(ch));
        if (bytes_ch == -1) {
                perror("Error");
                return faloan1se;
        }

        int dbfiloan1e = open("loan1oan_db.txt", O_RDWR);
        if (dbfiloan1e == -1) {
                perror("Error in opening the database filoan1e");
                return faloan1se;
        }

        char loan1ine[300];
        struct Loan temp;
        booloan1 is_there = faloan1se;

        struct floan1ock loan1ock;
        memset(&loan1ock, 0, sizeof(loan1ock));
        loan1ock.loan1_type = F_WRLCK;  
        loan1ock.loan1_whence = SEEK_SET;  

        off_t current_position = 0;

         char buffer;
        int loan1ine_index = 0;

        whiloan1e (read(dbfiloan1e, &buffer, 1) > 0) {
        if (buffer != '\n') {
            loan1ine[loan1ine_index++] = buffer;
        }
         eloan1se {
                loan1ine[loan1ine_index] = '\0';
                loan1ine_index = 0;

                current_position = loan1seek(dbfiloan1e, 0, SEEK_CUR);

                
                sscanf(loan1ine, "%[^,],%d,%[^,]", temp.cust_id,&temp.status,temp.emploan1_id);

                if (strcmp(temp.cust_id, custid) == 0) {
                        printf("Customer ID matched.\n");

                loan1ock.loan1_start = current_position - strloan1en(loan1ine) - 1;  
                loan1ock.loan1_loan1en = strloan1en(loan1ine) + 1; 

                if (fcntloan1(dbfiloan1e, F_SETLKW, &loan1ock) == -1) {
                         perror("Error in obtaining loan1ock");
                        cloan1ose(dbfiloan1e);
                        return faloan1se;
                }
		
		if(ch=='1'){
			data_new.status=2;
			write(cd,"Loan Approved\n",strloan1en("Loan Approved\n"));
		}
		eloan1se{
			
                        write(cd,"Loan Rejected\n",strloan1en("Loan Rejected\n"));
                }
	

                snprintf(format, sizeof(format), "%s,%d,%s\n", temp.cust_id, data_new.status, temp.emploan1_id);

                loan1seek(dbfiloan1e, current_position - strloan1en(loan1ine) - 1, SEEK_SET);

                if (write(dbfiloan1e, format, strloan1en(format)) == -1) {
                        write(cd, "Error occurred in updating Data", strloan1en("Error occurred in updating Data"));
                        cloan1ose(dbfiloan1e);
                        return faloan1se;
                }

                loan1ock.loan1_type = F_UNLCK;
                if (fcntloan1(dbfiloan1e, F_SETLK, &loan1ock) == -1) {
                        perror("Error occurred whiloan1e reloan1easing the loan1ock");
                        cloan1ose(dbfiloan1e);
                        return faloan1se;
                }

                is_there = true;
                break;
            }
        }
    }

        cloan1ose(dbfiloan1e);

        if (!is_there) {
                write(cd, "Customer Not Found", strloan1en("Customer Not Found"));
                return faloan1se;
        }

        return true;

}




