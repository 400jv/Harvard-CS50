import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    user_cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]['cash']
    stocks = db.execute("SELECT p.name, p.symbol, p.price, SUM(shares) AS total_owned FROM users as u INNER JOIN purchases as p ON p.user_id = u.id WHERE u.id = ? GROUP BY p.name", session["user_id"])

    total = user_cash

    for stock in stocks:
        total += stock["total_owned"] * stock["price"]

    return render_template("index.html", user_cash=user_cash, stocks=stocks, total=total, usd=usd)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "GET":
        return render_template("buy.html")

    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        if not symbol: return apology("Symbol is blank.")
        if not shares.isnumeric(): return apology("Shares is not a number.")

        stock = lookup(symbol)

        if not stock: return apology("This symbol does not exist.")

        user_cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]

        price = stock["price"] * float(shares)

        if user_cash["cash"] < price:
            return apology(f"You have US${user_cash}, so you can't buy the stock US${stock['price']}")

        db.execute("UPDATE users SET cash = (?) WHERE id = (?)", user_cash["cash"] - price, session["user_id"])
        db.execute("INSERT INTO purchases (user_id, name, symbol, price, shares) VALUES (?, ?, ?, ?, ?)", session["user_id"], stock["name"], stock["symbol"], stock["price"], shares)


    return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method == "GET":
        return render_template("quote.html")

    if request.method == "POST":
        quote = request.form.get("symbol")

        stock = lookup(quote)

    return render_template("/quoted.html", stock=stock)

@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "GET":
        return render_template("/register.html")


    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        passwordConfirmation = request.form.get("confirmation")

        if not username: return apology("OOPS! We need that you create a username")

        if not password: return apology("OOPS! We need that you create a password")

        if not passwordConfirmation: return apology("OOPS! We need that you confirm the password")

        if passwordConfirmation != password: return apology("OOPS! the password doesn't match with the confirmation")

        passwordHash = generate_password_hash(password, method='pbkdf2:sha256', salt_length=8)

        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, passwordHash)

    return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method == "GET":
        stocks = db.execute("SELECT symbol FROM purchases WHERE user_id = ? GROUP BY symbol", session["user_id"])

        return render_template("sell.html", stocks=stocks)

    if request.method == "POST":

        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        if not symbol: return apology("Symbol is blank.")

        if not shares.isnumeric(): return apology("Shares is not a number.")

        stocks = db.execute("SELECT p.name, p.symbol, p.price, SUM(shares) AS total_owned FROM users as u INNER JOIN purchases as p ON p.user_id = u.id WHERE u.id = ? AND p.symbol = ?", session["user_id"], symbol)

        print(stocks)

        if len(stocks) != 1 or stocks[0]["total_owned"] < int(shares): return apology("not enough shares")

        price = lookup(symbol)["price"] * int(shares)

        user_cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]

        db.execute("UPDATE users SET cash = (?) WHERE id = (?)", user_cash + price, session["user_id"])

        name = lookup(symbol)["name"]

        newShareAmount = stocks[0]["total_owned"] - int(shares)

        db.execute("INSERT INTO purchases (name, user_id, symbol, price, shares) VALUES (?, ?, ?, ?, ?)", name, session["user_id"], symbol, price, newShareAmount)

        flash(f"Sold {shares} of {name}")

        return redirect("/")

def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
