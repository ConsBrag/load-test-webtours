Action()
{
	lr_start_transaction("05_TicketPaymentNoView");
			
		web_set_sockets_option("SSL_VERSION", "AUTO");
		
		lr_start_transaction("goToSite");
	
	
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
		
		/*Correlation comment - Do not change!  Original value='129637.016929931zzzicAtpAfiDDDDDtAAAQpcctDf' Name ='userSession' Type ='ResponseBased'*/
			web_reg_save_param_attrib(
				"ParamName=userSession",
				"TagName=input",
				"Extract=value",
				"Name=userSession",
				"Type=hidden",
				SEARCH_FILTERS,
				"IgnoreRedirections=No",
				"RequestUrl=*/nav.pl*",
				LAST);
		
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
	
		lr_think_time(6);
		
		lr_start_transaction("login");
			
			web_revert_auto_header("Sec-Fetch-User");
		
			web_add_auto_header("Sec-Fetch-Dest", 
				"frame");
		
			web_revert_auto_header("Upgrade-Insecure-Requests");
		
			web_add_header("Origin", 
				"http://localhost:1080");
		
			web_add_auto_header("Sec-Fetch-Site", 
				"same-origin");
			
			web_reg_find("Fail=NotFound",
				"Text=User password was correct",
				LAST);
			
			//lr_save_string("cracow", "login11");

			//lr_save_string("quebec", "password11");

			web_submit_data("login.pl",
				"Action=http://localhost:1080/cgi-bin/login.pl",
				"Method=POST",
				"TargetFrame=body",
				"RecContentType=text/html",
				"Referer=http://localhost:1080/cgi-bin/nav.pl?in=home",
				"Snapshot=t2.inf",
				"Mode=HTML",
				ITEMDATA,
				"Name=userSession", "Value={userSession}", ENDITEM,
				"Name=username", "Value={login}", ENDITEM,
				"Name=password", "Value={password}", ENDITEM,
				"Name=login.x", "Value=70", ENDITEM,
				"Name=login.y", "Value=3", ENDITEM,
				"Name=JSFormSubmit", "Value=off", ENDITEM,
				LAST);
			
		lr_end_transaction("login", LR_AUTO);
	
		
		lr_start_transaction("click_flights");
		
			web_add_auto_header("Sec-Fetch-User", 
				"?1");
		
			web_add_auto_header("Upgrade-Insecure-Requests", 
				"1");
		
			web_reg_find("Fail=NotFound",
				"Text= User has returned to the search page",
				LAST);
		
			web_url("Search Flights Button", 
				"URL=http://localhost:1080/cgi-bin/welcome.pl?page=search", 
				"TargetFrame=body", 
				"Resource=0", 
				"RecContentType=text/html", 
				"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
				"Snapshot=t3.inf", 
				"Mode=HTML", 
				LAST);
		
		lr_end_transaction("click_flights", LR_AUTO);
		
		lr_think_time(18);
			
		web_add_auto_header("Origin", 
				"http://localhost:1080");
		
		lr_start_transaction("search_flights");
								
			if (atoi(lr_eval_string("{roundtrip}")) == 0){
					
				/*Correlation comment - Do not change!  Original value='023;401;09/18/2020' Name ='outboundFlight' Type ='ResponseBased'*/
				web_reg_save_param_attrib(
					"ParamName=outboundFlight",
					"TagName=input",
					"Extract=value",
					"Name=outboundFlight",
					//"Ordinal=ALL",
					"Type=radio",
					SEARCH_FILTERS,
					"IgnoreRedirections=No",
					LAST);
				
				//Flight departing from <B>Denver</B> to <B>London</B> on <B>09/18/2020</B>
				
				web_reg_find("Text=<B>{depart}</B> to <B>{arrive}</B> on <B>{departDate}</B>",
					LAST);
				
				web_reg_save_param("flight_id",
					"LB=name=\"outboundFlight\" value=\"",
					"RB=;",
					"Ord=ALL",
					LAST);

				//<td align="center">8am<td align="center">
				
				web_reg_save_param("flight_time",
					"LB=<td align=\"center\">",
					"RB=m<td align=\"center\">",
					"Ord=ALL",
					LAST);
				
				web_submit_data("reservations.pl",
					"Action=http://localhost:1080/cgi-bin/reservations.pl", 
					"Method=POST", 
					"TargetFrame=", 
					"RecContentType=text/html", 
					"Referer=http://localhost:1080/cgi-bin/reservations.pl?page=welcome", 
					"Snapshot=t4.inf", 
					"Mode=HTML", 
					ITEMDATA, 
					"Name=advanceDiscount", "Value={advanceDiscount}", ENDITEM, 
					"Name=depart", "Value={depart}", ENDITEM, 
					"Name=departDate", "Value={departDate}", ENDITEM, 
					"Name=arrive", "Value={arrive}", ENDITEM, 
					"Name=returnDate", "Value={returnDate}", ENDITEM, 
					"Name=numPassengers", "Value={numPassengers}", ENDITEM, 
					"Name=seatPref", "Value={seatPref}", ENDITEM, 
					"Name=seatType", "Value={seatType}", ENDITEM, 
					"Name=findFlights.x", "Value=63", ENDITEM, 
					"Name=findFlights.y", "Value=12", ENDITEM, 
					"Name=.cgifields", "Value=roundtrip", ENDITEM, 
					"Name=.cgifields", "Value=seatType", ENDITEM, 
					"Name=.cgifields", "Value=seatPref", ENDITEM, 
					LAST);
				} 
			
			else if (atoi(lr_eval_string("{roundtrip}")) == 1){
				
				/*Correlation comment - Do not change!  Original value='023;401;09/18/2020' Name ='outboundFlight' Type ='ResponseBased'*/
				web_reg_save_param_attrib(
					"ParamName=outboundFlight",
					"TagName=input",
					"Extract=value",
					"Name=outboundFlight",
					//"Ordinal=ALL",
					"Type=radio",
					SEARCH_FILTERS,
					"IgnoreRedirections=No",
					LAST);
			
				/*Correlation comment - Do not change!  Original value='201;437;09/21/2020' Name ='returnFlight' Type ='ResponseBased'*/
				web_reg_save_param_attrib(
					"ParamName=returnFlight",
					"TagName=input",
					"Extract=value",
					"Name=returnFlight",
					"Type=radio",
					SEARCH_FILTERS,
					"IgnoreRedirections=No",
					LAST);
					
				//Flight departing from <B>Denver</B> to <B>London</B> on <B>09/18/2020</B>
				
				web_reg_find("Text=<B>{depart}</B> to <B>{arrive}</B> on <B>{departDate}</B>",
		LAST);
				
				web_reg_save_param("flight_id",
					"LB=name=\"outboundFlight\" value=\"",
					"RB=;",
					"Ord=ALL",
					LAST);

				//<td align="center">8am<td align="center">
				
				web_reg_save_param("flight_time",
					"LB=<td align=\"center\">",
					"RB=m<td align=\"center\">",
					"Ord=ALL",
					LAST);
				
				web_submit_data("reservations.pl",
					"Action=http://localhost:1080/cgi-bin/reservations.pl", 
					"Method=POST", 
					"TargetFrame=", 
					"RecContentType=text/html", 
					"Referer=http://localhost:1080/cgi-bin/reservations.pl?page=welcome", 
					"Snapshot=t4.inf", 
					"Mode=HTML", 
					ITEMDATA, 
					"Name=advanceDiscount", "Value={advanceDiscount}", ENDITEM, 
					"Name=depart", "Value={depart}", ENDITEM, 
					"Name=departDate", "Value={departDate}", ENDITEM, 
					"Name=arrive", "Value={arrive}", ENDITEM, 
					"Name=returnDate", "Value={returnDate}", ENDITEM, 
					"Name=numPassengers", "Value={numPassengers}", ENDITEM, 
					"Name=roundtrip", "Value=on", ENDITEM, 
					"Name=seatPref", "Value={seatPref}", ENDITEM, 
					"Name=seatType", "Value={seatType}", ENDITEM, 
					"Name=findFlights.x", "Value=57", ENDITEM, 
					"Name=findFlights.y", "Value=3", ENDITEM, 
					"Name=.cgifields", "Value=roundtrip", ENDITEM, 
					"Name=.cgifields", "Value=seatType", ENDITEM, 
					"Name=.cgifields", "Value=seatPref", ENDITEM, 
					LAST);
				}
		lr_end_transaction("search_flights", LR_AUTO);
		
		lr_think_time(18);
		
		lr_save_string(lr_eval_string("outboundFlight_{random_id}"), "outboundFlight_id");
		
		lr_start_transaction("select_ticket");
		
			web_reg_find("Fail=NotFound",
				"Text=Flight Reservation",
				LAST);
		
			if (atoi(lr_eval_string("{roundtrip}")) == 0){
		
				web_submit_data("reservations.pl_2",
					"Action=http://localhost:1080/cgi-bin/reservations.pl", 
					"Method=POST", 
					"TargetFrame=", 
					"RecContentType=text/html", 
					"Referer=http://localhost:1080/cgi-bin/reservations.pl", 
					"Snapshot=t5.inf", 
					"Mode=HTML", 
					ITEMDATA, 
					"Name=outboundFlight", "Value={outboundFlight}", ENDITEM, 
					"Name=numPassengers", "Value={numPassengers}", ENDITEM, 
					"Name=advanceDiscount", "Value={advanceDiscount}", ENDITEM, 
					"Name=seatType", "Value={seatType}", ENDITEM, 
					"Name=seatPref", "Value={seatPref}", ENDITEM, 
					"Name=reserveFlights.x", "Value=40", ENDITEM, 
					"Name=reserveFlights.y", "Value=9", ENDITEM, 
					LAST);
				
				}
			
			else if (atoi(lr_eval_string("{roundtrip}")) == 1) {
			
				web_submit_data("reservations.pl_2",
					"Action=http://localhost:1080/cgi-bin/reservations.pl", 
					"Method=POST", 
					"TargetFrame=", 
					"RecContentType=text/html", 
					"Referer=http://localhost:1080/cgi-bin/reservations.pl", 
					"Snapshot=t5.inf", 
					"Mode=HTML", 
					ITEMDATA, 
					"Name=outboundFlight", "Value={outboundFlight}", ENDITEM, 
					"Name=returnFlight", "Value={returnFlight}", ENDITEM, 
					"Name=numPassengers", "Value={numPassengers}", ENDITEM, 
					"Name=advanceDiscount", "Value={advanceDiscount}", ENDITEM, 
					"Name=seatType", "Value={seatType}", ENDITEM, 
					"Name=seatPref", "Value={seatPref}", ENDITEM, 
					"Name=reserveFlights.x", "Value=40", ENDITEM, 
					"Name=reserveFlights.y", "Value=9", ENDITEM, 
					LAST);
				}
		
		lr_end_transaction("select_ticket", LR_AUTO);
		
		lr_think_time(27);
		
		lr_start_transaction("pay_ticket");
		
			web_revert_auto_header("Origin");
		
			web_revert_auto_header("Sec-Fetch-User");
		
			web_revert_auto_header("Upgrade-Insecure-Requests");
		
			web_add_header("Origin", 
				"http://localhost:1080");
			
			web_reg_find("Fail=NotFound",
				"Text=Reservation Made",
				LAST);
			
			if (atoi(lr_eval_string("{numPassengers}")) == 1){
			
				//09/19/2020 :  8am : Flight 020 leaves Denver  for London
				
				//{flight_time}m : Flight {flight_id}
				
				//lr_save_string(lr_eval_string("flight_time_{random_id})"), "flight_time_id");
				               
				//lr_save_string(lr_eval_string("flight_num_{random_id})"), "flight_num_id");
				
				//web_reg_find("Text={departDate} :  {flight_time_id}m : Flight {flight_num_id} leaves {depart}  for {arrive}",
		//LAST);
				
				web_submit_data("reservations.pl_3",
					"Action=http://localhost:1080/cgi-bin/reservations.pl", 
					"Method=POST", 
					"TargetFrame=", 
					"RecContentType=text/html", 
					"Referer=http://localhost:1080/cgi-bin/reservations.pl", 
					"Snapshot=t6.inf", 
					"Mode=HTML", 
					ITEMDATA, 
					"Name=firstName", "Value={firstName}", ENDITEM, 
					"Name=lastName", "Value={lastName}", ENDITEM, 
					"Name=address1", "Value={address1}", ENDITEM, 
					"Name=address2", "Value={address2}", ENDITEM, 
					"Name=pass1", "Value={pass1}", ENDITEM, 
					"Name=creditCard", "Value={creditCard}", ENDITEM, 
					"Name=expDate", "Value={expDate}", ENDITEM, 
					"Name=oldCCOption", "Value=", ENDITEM, 
					"Name=numPassengers", "Value={numPassengers}", ENDITEM, 
					"Name=seatType", "Value={seatType}", ENDITEM, 
					"Name=seatPref", "Value={seatPref}", ENDITEM, 
					"Name=outboundFlight", "Value={outboundFlight}", ENDITEM, 
					"Name=advanceDiscount", "Value={advanceDiscount}", ENDITEM, 
					"Name=returnFlight", "Value=returnFlight", ENDITEM, 
					"Name=JSFormSubmit", "Value=off", ENDITEM, 
					"Name=buyFlights.x", "Value=70", ENDITEM, 
					"Name=buyFlights.y", "Value=11", ENDITEM, 
					"Name=.cgifields", "Value=saveCC", ENDITEM, 
					LAST);
			
			}
				
			else if (atoi(lr_eval_string("{numPassengers}")) == 2){
				
				web_submit_data("reservations.pl_3", 
					"Action=http://localhost:1080/cgi-bin/reservations.pl", 
					"Method=POST", 
					"TargetFrame=", 
					"RecContentType=text/html", 
					"Referer=http://localhost:1080/cgi-bin/reservations.pl", 
					"Snapshot=t6.inf", 
					"Mode=HTML", 
					ITEMDATA, 
					"Name=firstName", "Value={firstName}", ENDITEM, 
					"Name=lastName", "Value={lastName}", ENDITEM, 
					"Name=address1", "Value={address1}", ENDITEM, 
					"Name=address2", "Value={address2}", ENDITEM, 
					"Name=pass1", "Value={pass1}", ENDITEM, 
					"Name=pass2", "Value={pass2}", ENDITEM, 
					"Name=creditCard", "Value={creditCard}", ENDITEM, 
					"Name=expDate", "Value={expDate}", ENDITEM, 
					"Name=oldCCOption", "Value=", ENDITEM, 
					"Name=numPassengers", "Value={numPassengers}", ENDITEM, 
					"Name=seatType", "Value={seatType}", ENDITEM, 
					"Name=seatPref", "Value={seatPref}", ENDITEM, 
					"Name=outboundFlight", "Value={outboundFlight}", ENDITEM, 
					"Name=advanceDiscount", "Value={advanceDiscount}", ENDITEM, 
					"Name=returnFlight", "Value={returnFlight}", ENDITEM, 
					"Name=JSFormSubmit", "Value=off", ENDITEM, 
					"Name=buyFlights.x", "Value=70", ENDITEM, 
					"Name=buyFlights.y", "Value=11", ENDITEM, 
					"Name=.cgifields", "Value=saveCC", ENDITEM, 
					LAST);
			}
				
			else if (atoi(lr_eval_string("{numPassengers}")) == 3){
				
				web_submit_data("reservations.pl_3", 
					"Action=http://localhost:1080/cgi-bin/reservations.pl", 
					"Method=POST", 
					"TargetFrame=", 
					"RecContentType=text/html", 
					"Referer=http://localhost:1080/cgi-bin/reservations.pl", 
					"Snapshot=t6.inf", 
					"Mode=HTML", 
					ITEMDATA, 
					"Name=firstName", "Value={firstName}", ENDITEM, 
					"Name=lastName", "Value={lastName}", ENDITEM, 
					"Name=address1", "Value={address1}", ENDITEM, 
					"Name=address2", "Value={address2}", ENDITEM, 
					"Name=pass1", "Value={pass1}", ENDITEM, 
					"Name=pass2", "Value={pass2}", ENDITEM, 
					"Name=pass3", "Value={pass3}", ENDITEM, 
					"Name=creditCard", "Value={creditCard}", ENDITEM, 
					"Name=expDate", "Value={expDate}", ENDITEM, 
					"Name=oldCCOption", "Value=", ENDITEM, 
					"Name=numPassengers", "Value={numPassengers}", ENDITEM, 
					"Name=seatType", "Value={seatType}", ENDITEM, 
					"Name=seatPref", "Value={seatPref}", ENDITEM, 
					"Name=outboundFlight", "Value={outboundFlight}", ENDITEM, 
					"Name=advanceDiscount", "Value={advanceDiscount}", ENDITEM, 
					"Name=returnFlight", "Value=returnFlight", ENDITEM, 
					"Name=JSFormSubmit", "Value=off", ENDITEM, 
					"Name=buyFlights.x", "Value=70", ENDITEM, 
					"Name=buyFlights.y", "Value=11", ENDITEM, 
					"Name=.cgifields", "Value=saveCC", ENDITEM, 
					LAST);
					
			}
			
		lr_end_transaction("pay_ticket", LR_AUTO);
	
		lr_think_time(18);
		
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
				"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=flights", 
				"Snapshot=t7.inf", 
				"Mode=HTML", 
				LAST);
		
		lr_end_transaction("logout", LR_AUTO);

	
	lr_end_transaction("05_TicketPaymentNoView", LR_AUTO);

	return 0;
}