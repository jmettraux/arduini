
require 'sinatra/base'

#$: << 'lib'

class App < Sinatra::Base

  #set :bind, '0.0.0.0'
  #set :bind, '10.0.1.3'
    # using `rackup -o 0.0.0.0` instead

  set :show_exceptions, true

  get '/' do
    "ok\n"
  end

  post '/' do
    puts request_body
    "ok\n"
  end
end

run App

