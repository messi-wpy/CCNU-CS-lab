/*3.1---a*/
select title 
from course 
where dept_name ="Comp. Sci." and credits >= 3;

/*3.1---b*/
select distinct  student.ID  
from (teaches join instructor using(ID)) 
join (student join takes using (ID)) using (course_id) 
where instructor.name='Einstein'; 

/*3.1---c*/
select max(salary) 
from instructor; 

/*3.1---d*/
select name 
from instructor 
 where salary =(select max(salary)from instructor); 

/*3.1---e*/
select course_id,sec_id ,count(ID) 
from section natural join takes 
where semester='Fall' and year=2009 
group by sec_id,course_id ; 

/*3.1---f*/
 select max(mostman) 
                              from( 
                               select course_id,sec_id,count(ID) as mostman 
                               from section natural join takes 
                               where semester="Fall" and year=2009 
                               group by course_id,sec_id 
                               )as T; 
                               
/*3.1---g*/
select course_id,sec_id 
from( 
select course_id,sec_id,count(ID)as num 
from section natural join takes 
 where semester="Fall" and year=2009 
  group by course_id ,sec_id  
  )as T 
  where num=(select max(num) 
   from (select course_id,sec_id,count(ID)as num 
from section natural join takes 
 where semester="Fall" and year=2009 
  group by course_id ,sec_id  
  )as T2  );

/*3.2建立关系*/
create table grade_points(
			grade varchar (2) ,
			points numeric(3,0),
            primary key (grade)
            );
show tables;

insert into grade_points values ('A',4),('A-',3.7),('B+',3.3),('B',3);
select * from grade_points;
/*3.2  a*/
select sum(credits * points)   
from (takes natural join course) natural join grade_points
where ID ='12345';  
/*3.3 b*/
select sum(credits * points)/sum(credits) as GPA
from (takes natural join course) natural join grade_points
where ID ='12345'; 

/*3.2  c*/
select ID, sum(credits * points)/sum(credits) as GPA
from (takes natural join course) natural join grade_points
group by ID;

/*3.3 a*/
desc instructor;
select salary,name
from instructor;
update instructor set salary=salary*1.1;

/*3.3 b*/
select course_id from course;
delete 
from course
where course_id not in (select course_id from section);

/*3.3c*/
insert into instructor
select ID,name,dept_name, 10000
from student
where tot_cred>100;

/*3.5 a*/
create table marks(ID varchar(10),score numeric(3,1));
insert into marks value ('2017',78);

/*3.6 */
select dept_name
from department
where lower(dept_name)like "%sci%";

 /*3.7 查询p的a1字段与r1或r2相等的时候，如果p的a1
为空则没有，如果p的a1与r1和r2中的都不相等，也为空*/                             

/*3.8  a*/
select customer_name 
from depositor
where customer_name not in(select customer_name from borrower );

/*3.8 b*/

select customer_name
from customer 
where customer_city not in(
	select customer_city
    from customer
    where customer_name="Smith"
)  and customer_street not in( select customer_street from customer where customer_name='Smith');


/*3.8 c*/
select distinct branch_name
from account natural join depositor natural join customer
where customer_city = 'Harrison';
                               
/*3.9  a*/
select employee_name,city
from employee natural join works
where company_name='First Bank Corporation';

/*3.9 b*/
with sa as(select employee_name
from works
where company_name = 'First Bank Corporation' and salary > 10000)
select *
from employee natural join sa;

/*3.9 c*/
select employee_name
from works
where company_name <>'First Bank Corporation';

/*3.9 d*/
select employee_name
from works
where salary > all(
	select salary
    from works
    where company_name='Small Bank Corporation'
);

/*3.9 e*/
select company_name
from company
where city in (
select city 
from company
where company_name='Small Bank Corporation'
);

/*3.9 f*/
select company_name
from works
group by company_name
having count(distinct employee_name)>=all(
select count(distinct employee_name)
from works
group by company_name
);

/*3.9 g*/
select company_name
from works
group by company_name
having avg(salary) >(
 select avg(salary)
 from works
 group by company_name
);

/*3.10 a*/
update employee
set city = 'Newton'
where employee_name = 'Jones';

/*3.10 b*/
update works set salary=salary*1.1 
where company_name='First Bank Corporation' and salary <= 100000 and employee_name in (
	select employee_name
    from managers
);

update works set salary=salary*1.03 
where company_name='First Bank Corporation' and salary > 100000 and employee_name in (
	select employee_name
    from managers
);


/* 第四章练习题*/
/* 4.1 a*/
select distinct ID ,name
from instructor natural left outer join teaches;

/* 4.1 b*/
select distinct teaches.ID,name
from teaches,instructor
where teaches.ID=instructor.ID;

/*4.1 c*/
select course_id,sec_id,ID
from (section natural left outer join teaches ) natural left outer join instructor
where semester="Spring" and year=2010;
/*4.1 d*/
select dept_name, count( ID )
from department natural left outer join instructor
group by dept_name;

/*4.2 a*/
select * from student natural join takes
union
select ID , name, dept_name, tot_cred, NULL, NULL, NULL, NULL, NULL
from student S1 where not exists
(select ID from takes T1 where T1.id = S1.id);

/*4.3 a r = (a,b), s = (x,y), t = (b,d).*/
/*4.3 b  不可能








