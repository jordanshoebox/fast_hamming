
Gem::Specification.new "fast_hamming", "1.0" do |s|
  s.name = 'fast_hamming'
  s.summary = 'calculate hamming distances, quickly'
  s.authors = ['Jordan Stinson']
  s.extensions = %w[ext/extconf.rb]
  s.require_paths = ['lib', 'ext']
  s.files = Dir['lib/**/*.rb'] + Dir['ext/**/*.c'] + Dir['ext/**/extconf.rb']
end
