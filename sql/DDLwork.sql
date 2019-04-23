/*建立银行数据库*/
create database bank;
use bank;
create table branch(
	branch_name    varchar(20),
    branch_city    varchar(20),
    assets         varchar(20),
    primary key (branch_name)

);
create table customer(
	customer_name  varchar(20) primary key,
    customer_street varchar(20),
    customer_city varchar(20)
);
create table loan(
	loan_number  numeric(10,3) primary key,
    branch_name  varchar(20),
    amount   numeric(10,3)
);
create table borrower(
	customer_name  varchar(20),
    loan_number   numeric(10,3),
    primary key(customer_name,loan_number)
);

create table account(
	account_number  numeric(10,3)primary key,
    branch_name  numeric(10,3),
    balance numeric(10,3)
);

create table depositor(
	customer_name varchar(20),
    account_number varchar(20),
    primary key(customer_name,account_number)

);

/*创建雇员数据库*/
create database Employee;
use Employee;
create table employee(
	employee_name varchar(20) primary key,
    street  varchar(20) ,
    city   varchar(20)
);

create table works(
	employee_name varchar(20)primary key,
    company_name varchar(20),
    salary numeric(10,3)
);

create table company(
	company_name varchar(20)primary key,
    city varchar(20)
);

create table managers(
	employee_name varchar(20)primary key,
    manager_name varchar(20)
);












