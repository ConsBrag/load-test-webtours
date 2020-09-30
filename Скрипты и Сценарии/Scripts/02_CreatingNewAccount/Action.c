Action()
{
	lr_start_transaction("02_CreatingNewAccount");
	
		lr_start_transaction("goToSite");

			web_set_sockets_option("SSL_VERSION", "AUTO");
		
			web_add_auto_header("Sec-Fetch-Site", 
				"none");
		
			web_add_auto_header("Sec-Fetch-Dest", 
				"document");
		
			web_add_auto_header("Sec-Fetch-Mode", 
				"navigate");
		
			web_add_auto_header("Sec-Fetch-User", 
				"?1");
		
			web_add_auto_header("Upgrade-Insecure-Requests", 
				"1");
		
			web_reg_find("Fail=NotFound",
				"Text=Web Tours",
				LAST);
			
			web_url("WebTours", 
				"URL=http://localhost:1080/WebTours/", 
				"TargetFrame=", 
				"Resource=0", 
				"RecContentType=text/html", 
				"Referer=", 
				"Snapshot=t1.inf", 
				"Mode=HTML", 
				LAST);
			
		lr_end_transaction("goToSite", LR_AUTO);

		lr_think_time(4);
		
		lr_start_transaction("createNewAcc");

			web_add_auto_header("Sec-Fetch-Dest", 
				"frame");
		
			web_revert_auto_header("Sec-Fetch-User");
		
			web_revert_auto_header("Upgrade-Insecure-Requests");
		
			web_add_auto_header("Sec-Fetch-Site", 
				"same-origin");
			
			web_reg_find("Fail=NotFound",
				"Text=User Information",
				LAST);
		
			web_url("sign up now", 
				"URL=http://localhost:1080/cgi-bin/login.pl?username=&password=&getInfo=true", 
				"TargetFrame=body", 
				"Resource=0", 
				"RecContentType=text/html", 
				"Referer=http://localhost:1080/WebTours/home.html", 
				"Snapshot=t2.inf", 
				"Mode=HTML", 
				LAST);
		
		lr_end_transaction("createNewAcc", LR_AUTO);

		lr_think_time(10);
		
		lr_start_transaction("login");

			web_add_header("Origin", 
				"http://localhost:1080");
		
			web_add_auto_header("Sec-Fetch-User", 
				"?1");
		
			web_add_auto_header("Upgrade-Insecure-Requests", 
				"1");
					
			web_reg_find("Fail=NotFound",
				"Text=Welcome to Web Tours",
				LAST);
		
			web_submit_data("login.pl", 
				"Action=http://localhost:1080/cgi-bin/login.pl", 
				"Method=POST", 
				"TargetFrame=info", 
				"RecContentType=text/html", 
				"Referer=http://localhost:1080/cgi-bin/login.pl?username=&password=&getInfo=true", 
				"Snapshot=t3.inf", 
				"Mode=HTML", 
				ITEMDATA, 
				"Name=username", "Value={login}", ENDITEM, 
				"Name=password", "Value={password}", ENDITEM, 
				"Name=passwordConfirm", "Value={password}", ENDITEM, 
				"Name=firstName", "Value={firstName}", ENDITEM, 
				"Name=lastName", "Value={lastName}", ENDITEM, 
				"Name=address1", "Value={address1}", ENDITEM, 
				"Name=address2", "Value={address2}", ENDITEM, 
				"Name=register.x", "Value=76", ENDITEM, 
				"Name=register.y", "Value=1", ENDITEM, 
				LAST);
		
		lr_end_transaction("login", LR_AUTO);
				
		lr_think_time(10);

		lr_start_transaction("continue");
	
			web_revert_auto_header("Sec-Fetch-User");
		
			web_revert_auto_header("Upgrade-Insecure-Requests");
			
			web_reg_find("Fail=NotFound",
				"Text=User has returned to the home page",
				LAST);
		
			web_url("button_next.gif", 
				"URL=http://localhost:1080/cgi-bin/welcome.pl?page=menus", 
				"TargetFrame=body", 
				"Resource=0", 
				"RecContentType=text/html", 
				"Referer=http://localhost:1080/cgi-bin/login.pl", 
				"Snapshot=t4.inf", 
				"Mode=HTML", 
				LAST);
			
		lr_end_transaction("continue", LR_AUTO);

		
		lr_start_transaction("logout");

			web_add_header("Sec-Fetch-User", 
				"?1");
		
			web_add_header("Upgrade-Insecure-Requests", 
				"1");
		
			web_reg_find("Fail=NotFound",
				"Text=A Session ID has been created and loaded into a cookie called",
				LAST);
		
			web_url("SignOff Button", 
				"URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=1", 
				"TargetFrame=body", 
				"Resource=0", 
				"RecContentType=text/html", 
				"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
				"Snapshot=t5.inf", 
				"Mode=HTML", 
				LAST);
		
		lr_end_transaction("logout", LR_AUTO);

	
	lr_end_transaction("02_CreatingNewAccount", LR_AUTO);

	return 0;
}