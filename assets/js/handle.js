const start_btn = document.querySelector(".start_btn button");
const info_box = document.querySelector(".info_box");
const exit_btn  = info_box.querySelector(".buttons .quit");
const continue_btn = info_box.querySelector(".buttons .restart");
const quiz_box = document.querySelector(".quiz_box");
const option_list = document.querySelector(".option_list");
const time_count = quiz_box.querySelector(".timer .timer_sec")
const time_line = quiz_box.querySelector("header .time_line");
const time_off = quiz_box.querySelector("header .time_text");


//if  start_btn clicked
start_btn.onclick = () =>{
    info_box.classList.add("activeInfo");
    
}


exit_btn.onclick = () =>{
    info_box.classList.remove("activeInfo");
}

continue_btn.onclick = () =>{
    info_box.classList.remove("activeInfo");
    quiz_box.classList.add("activeQuiz");
    showQuestion(0);
    queCounter(1);
    startTimer(30);
    startTimerLine(0);
}

let que_count = 0;
let que_numb =1;
let counter;
let counterLine;
let timeValue = 30;
let widthValue = 0;
let userScore = 0;

const next_btn = quiz_box.querySelector(".next_btn");
const result_box = document.querySelector(".result_box");
const restart_quiz = result_box.querySelector(".buttons .restart");
const quit = result_box.querySelector(".buttons .quit");

quit.onclick = ()=>{
    window.location.reload(); //reload the current window
}

restart_quiz.onclick = ()=>{
    quiz_box.classList.add("activeQuiz");
    result_box.classList.remove("activeResult");
    timeValue = 30; 
    que_count = 0;
    que_numb = 1;
    userScore = 0;
    widthValue = 0;
    showQuestion(que_count);
    queCounter(que_numb);
    clearInterval(counter);
    startTimer(timeValue);
    clearInterval(counterLine);
    startTimerLine(widthValue);
    next_btn.style.display = "none"; 
    time_off.textContent = "Time Left";
   
}

next_btn.onclick = ()=>{
    if(que_count < questions.length - 1){
        que_count++;
        que_numb++;
        showQuestion(que_count);
        queCounter(que_numb);
        clearInterval(counter);
        startTimer(timeValue);
        clearInterval(counterLine);
        startTimerLine(widthValue);
        next_btn.style.display = "none"; 
        time_off.textContent = "Time Left";
    }else{
        let player_name = document.getElementById("nameTxt").value;
        clearInterval(counter);
        clearInterval(counterLine);
        saveScore(player_name, userScore);
        console.log("Question completed");
        showResultBox();
    }
}

function showQuestion(index){
    const que_text = document.querySelector(".que_text");
    let que_tag =  '<span>'+ que_numb + ". " + questions[index].question +'</span>';
    let option_tag = ' <div class="option"><span>'+ questions[index].opt1 +'</span></div>'
                    + '<div class="option"><span>'+ questions[index].opt2 +'</span></div>'
                    + '<div class="option"><span>'+ questions[index].opt3 +'</span></div>'
                    + '<div class="option"><span>'+ questions[index].opt4 +'</span></div>';
    que_text.innerHTML = que_tag;
    option_list.innerHTML = option_tag;
    const option = option_list.querySelectorAll(".option");
    for(let i = 0; i < option.length; i++){
        option[i].setAttribute("onclick", "optionSeclected(this)");
    }
}

let tickIcon = '<div class="icon tick"><i class="fa fa-check"></i></div>';
let crossIcon = '<div class="icon cross"><i class="fa fa-times"></i></div>';

function optionSeclected(answer){
    clearInterval(counter);
    clearInterval(counterLine);
    let userAns = answer.textContent;
    let correctAns = questions[que_count].answer;
    let allOptions = option_list.children.length;
    if(userAns == correctAns){
        userScore += 10;
        console.log(userScore);
        answer.classList.add("correct");
        console.log("Answer is correct");
        answer.insertAdjacentHTML('beforeend', tickIcon);
    }else{
        answer.classList.add("incorrect")
        console.log("Answer is wrong");
        answer.insertAdjacentHTML('beforeend', crossIcon);

        for(let i =0 ; i < allOptions; i++){
            if(option_list.children[i].textContent == correctAns){
                option_list.children[i].setAttribute("class", "option correct");
                option_list.children[i].insertAdjacentHTML('beforeend', tickIcon);
            }   
        }
    }
    //disable all option if user selected
    for(let i =0 ; i < allOptions; i++){
        option_list.children[i].classList.add("disabled");
    }
    next_btn.style.display = "block";
}

function showResultBox(){
    info_box.classList.remove("activeInfo"); 
    quiz_box.classList.remove("activeQuiz"); 
    result_box.classList.add("activeResult"); 
    const scoreText = result_box.querySelector(".score_text");
    if(userScore > 60){
        let scoreTag = '<span>and congrats! You got <p>'+ userScore +'</p>out of <p>'+ (questions.length*10) +'</p></span>';
        scoreText.innerHTML = scoreTag;
    }else if(userScore > 40){
        let scoreTag = '<span>and nice, You got <p>'+ userScore +'</p>out of <p>'+ (questions.length*10) +'</p></span>';
        scoreText.innerHTML = scoreTag;
    }else{
        let scoreTag = '<span>and sorry, You got only <p>'+ userScore +'</p>out of <p>'+ (questions.length*10) +'</p></span>';
        scoreText.innerHTML = scoreTag;
    }
}

function startTimer(time){
    counter = setInterval(timer, 1000);
    function timer(){
        time_count.textContent = time;
        time--;
        if(time < 0){

            clearInterval(counter);
            time_count.textContent = '0';
            time_off.textContent = 'Time Off';
            const allOptions = option_list.children.length;
            let correctAns = questions[que_count].answer;
            for(let i =0 ; i < allOptions; i++){
                if(option_list.children[i].textContent == correctAns){
                    option_list.children[i].setAttribute("class", "option correct");
                    option_list.children[i].insertAdjacentHTML('beforeend', tickIcon);
                }   
            }
            for(let i =0 ; i < allOptions; i++){
                option_list.children[i].classList.add("disabled");
            }
            next_btn.style.display = "block";
        }
    }
    
}

function startTimerLine(time){
    counterLine = setInterval(timer, 56);
    function timer(){
        time += 1; //upgrading time value with 1
        time_line.style.width = time + "px"; //increasing width of time_line with px by time value
        if(time > 549){ //if time value is greater than 549
            clearInterval(counterLine); //clear counterLine
        }
    }
}

function queCounter(index){
    const bottom_ques_counter = quiz_box.querySelector(".total_que");
    let totalQuesCountTag =  '<span><p>'+ index + '</p>of<p>'+ questions.length +'</p>Question</span>';
    bottom_ques_counter.innerHTML = totalQuesCountTag; 
}

