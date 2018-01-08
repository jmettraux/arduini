
BEXEC:=bundle exec
RUBY:=$(BEXEC) ruby

serve:
	$(BEXEC) rackup -o 0.0.0.0 -p 8080 -s thin lib/serve.ru
s: serve

