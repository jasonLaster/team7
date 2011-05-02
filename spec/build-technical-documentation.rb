spec_dir = "../spec/"
src_dir = "./"

@o = File.open("#{spec_dir}technical-spec", "w")


def parseline(line)
  line = line.gsub(/#/,'\#').gsub(/\*/,'\*').gsub(/\/\/.+/,"")
  line = line.gsub(/(\S+)\(/, '`\1`(')
  showline = line[/\(/] && line[/\w+/]
  @o.puts "#{line}\n" if showline
end

def printfileheader(file_name)
  @o.puts "###{file_name}"
end

def printfilefooter
  @o.puts "\n\n"
end

def printheader
  @o.puts "#Technical Documenation\n"
end

printheader()

ARGV.each do |file|
  printfileheader(file)
  File.open("#{src_dir}#{file}", "r").readlines.each {|line| parseline(line)}
  printfilefooter()
end