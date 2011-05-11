
output = File.open("output", "r").readlines
clean_output = File.open("clean_output", "w")

# split the output into groups of file or function warnings
groups = []
group = []
output.each do |line|
  if line[/(In file|In function)/]
    groups << group
    group = [line]
  else
    group << line
  end
end


# delete group if any of the lines match a pattern
groups.delete_if do |lines|
  lines.any? do |line|
    line[/warning: ISO C restricts enumerator values to range of/]
  end
end


# remove lines that match a pattern
groups.map do |lines|
  lines.delete_if do |line|
    line[/gtk_.+incompatible pointer type/] ||
    line[/^gcc -c/] ||
    line[/^\n/]
  end
end

# delete warning group if all the warnings have been removed
groups.delete_if {|lines| lines.length <= 1}

# PRINT TO SCREEN
clean_output.puts groups.map(&:join).join("\n")

clean_output.puts "\n\nHIDDEN VALUES: \n" +
"gtk incompatible pointer type\n" +
"ISO C enumerator values\n"


# COLORIZE things
# doesn't yet work
def colorize(text, color_code)
  "#{color_code}#{text}e[0m"
end

def red(text); colorize(text, "e[31m"); end
def green(text); colorize(text, "e[32m"); end

OKBLUE = '\033[94m'
ENDC = '\033[0m'

